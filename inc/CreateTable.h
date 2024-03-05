#pragma once

#include <CSVLoad>

#include <iostream>
#include <optional>

namespace tools {
class CreateTable
{
public:
  /// @brief Constructor
  /// @param fname CSV File name
  CreateTable(const std::string& fname)
  {
    using namespace std;

    CSVLoad datas(fname);
    auto data = datas.getData();

    head_ = datas.getHeader();

    vector<map<const string, string>> data_v(data.begin()->second.size());

    for(auto p : data)
    {
      auto it = data_v.begin();
      for(auto d : p.second) (*it)[p.first] = d, it++;
    }

    datas_ = data_v;
  }

  /// @brief Destructor
  ~CreateTable()
  {
    head_.clear();
    datas_.clear();
  }

  /// @brief print
  /// @param tag Sort by tag
  std::string get_Table(const std::optional<std::string>& tag = std::nullopt)
  {
    using namespace std;

    ostringstream oss;

    vector<size_t> len;
    multimap<string, std::map<const std::string, std::string>> datas;

    auto s_tag = tag ? tag.value() : head_[0];

    for(auto m : datas_) datas.emplace(m[s_tag], m);

    for(auto h : head_) len.push_back(h.size());
    
    for(auto d : datas)
    {
      auto it = len.begin();
      for(auto h : head_) (*it) = max((*it), d.second[h].size()), it++;
    }

    auto sum = 0u;
    for(auto n : len) sum += n;

    sum += (head_.size() - 1)*3;
    sum += (sum % 2 == 0) ? 1u : 0u;

    string title = "Sorted Result";

    auto blank = (sum-title.size())/2;
    for(decltype(sum)_ = 0; _ < blank; _++) oss << " ";
    oss << title << endl;
    
    for(decltype(sum)_ = 0; _ < sum; _++) oss << "-";
    oss << endl;

    auto it = len.begin();
    for(auto h : head_)
    {
      blank = (*it);
      if(h == head_.front()) for(decltype(blank)_ = 0u; _ < blank; _++) oss << " ";
      else 
      {
        for(decltype(blank)_ = 0u; _ < (blank-h.size())/2; _++) oss << " ";
        oss << h;
        blank -= (blank-h.size())/2 + h.size();
        for(decltype(blank)_ = 0u; _ < blank; _++) oss << " ";
      }
      if(h != head_.back()) oss << " ╎ ";
      it++;
    }
    oss << endl;

    for(decltype(sum)_ = 0; _ < sum; _++) oss << "-";
    oss << endl;

    for(auto d : datas)
    {
      it = len.begin();
      for(auto s : head_)
      {
        auto t = d.second[s];
        auto n = (*it) - t.size();
        for(decltype(n)_ = 0; _ < n; _++) oss << " ";
        oss << t;
        if(s != head_.back()) oss << " ╎ ";
        it++;
      }
      oss << endl;
    }

    return oss.str();
  }

private:
  /// @brief Header
  std::vector<std::string> head_;

  /// @brief CSV Data
  /// @note vector<map<tag, data>>
  std::vector<std::map<const std::string, std::string>> datas_;
};
} // namespace tools