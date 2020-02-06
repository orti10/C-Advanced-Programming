#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <regex>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<QueryBase> QueryBase::factory(const string& s){

  // if(s == "some_word") return std::shared_ptr<QueryBase>(new WordQuery("some_word"));
  regex regexWords("^\\s*([\\w']+)\\s*$");
  regex NOTregexWords("^\\s*NOT\\s+([\\w']+)\\s*$");
  regex ANDregexWords("^\\s*([\\w']+)\\s+AND\\s+([\\w']+)\\s*$");
  regex ORregexWords("^\\s*([\\w']+)\\s+OR\\s+([\\w']+)\\s*$");
  regex NregexWords("^\\s*([\\w']+)\\s+([\\d]+)\\s+([\\w']+)\\s*$");
  if(regex_match(s,regexWords)){
    auto areMatchesRegex = sregex_iterator(s.begin(), s.end(), regexWords);
    return std::shared_ptr<QueryBase>(new WordQuery(areMatchesRegex->str()));
  }
  else if(regex_match(s,NOTregexWords)){
    auto areMatchesRegex = sregex_iterator(s.begin(), s.end(), NOTregexWords);
    return std::shared_ptr<QueryBase>(new NotQuery(areMatchesRegex->str().substr(4,areMatchesRegex->str().length())));
  }
  else if(regex_match(s,ANDregexWords)){
    auto begin = sregex_iterator(s.begin(), s.end(), ANDregexWords);
    return shared_ptr<QueryBase>(new AndQuery((*begin)[1].str(), (*begin)[2].str()));
  }
  else if(regex_match(s,ORregexWords)){
    auto begin = sregex_iterator(s.begin(), s.end(), ORregexWords);
    return shared_ptr<QueryBase>(new OrQuery((*begin)[1].str(), (*begin)[2].str()));
  }
  else if(regex_match(s,NregexWords)){
    istringstream sstream(s);
		vector<string> svec((istream_iterator<string>(sstream)),istream_iterator<string>());
    string first = svec[0];
    int k = stoi(svec[1]);
    string second = svec[2];
    return shared_ptr<QueryBase>(new NQuery(first, second, k)); 
  }
  else{
    throw invalid_argument ("Unrecognized search");
  }
}
////////////////////////////////////////////////////////////////////////////////

QueryResult NotQuery::eval(const TextQuery &text) const
{
  QueryResult result = text.query(query_word);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  auto beg = result.begin(), end = result.end();
  auto sz = result.get_file()->size();
  
  for (size_t n = 0; n != sz; ++n)
  {
    if (beg==end || *beg != n)
		ret_lines->insert(n);
    else if (beg != end)
		++beg;
  }
  return QueryResult(rep(), ret_lines, result.get_file());
    
}
////////////////////////////////////////////////////////////////////////////////

QueryResult AndQuery::eval (const TextQuery& text) const
{
  QueryResult left_result = text.query(left_query);
  QueryResult right_result = text.query(right_query);
  
  auto ret_lines = std::make_shared<std::set<line_no>>();
  std::set_intersection(left_result.begin(), left_result.end(),
      right_result.begin(), right_result.end(), 
      std::inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(rep(), ret_lines, left_result.get_file());
}
////////////////////////////////////////////////////////////////////////////////

QueryResult OrQuery::eval(const TextQuery &text) const
{
  QueryResult left_result = text.query(left_query);
  QueryResult right_result = text.query(right_query);
  
  auto ret_lines = 
      std::make_shared<std::set<line_no>>(left_result.begin(), left_result.end());

  ret_lines->insert(right_result.begin(), right_result.end());

  return QueryResult(rep(), ret_lines, left_result.get_file());
}
/////////////////////////////////////////////////////////

QueryResult NQuery::eval(const TextQuery &text) const
{
  QueryResult QResult = AndQuery::eval(text);
  regex firstWord(left_query);
  regex secondWord(right_query);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  auto it = QResult.begin();
  for (; it != QResult.end(); ++it){
    string currentLine = QResult.get_file()->at(*it);
    std::smatch match;
    regex_search(currentLine, match, firstWord);
    int firstPos=match.position(0);
    int index=firstPos + match.length();
    regex_search(currentLine,match,secondWord);
    int secondPosition=match.position(0);
    int numOfWords=0;
    bool flag = true;
    while(index < secondPosition-1){
      if(std::isspace(currentLine[index])){
        flag = true;
      }
      else if(flag){
        numOfWords++;
        flag = false;
      }
      ++index;
    }
    if(numOfWords <= dist){
      ret_lines->insert(*it);
    }
  }
  return QueryResult(rep(), ret_lines, QResult.get_file());
}