#include "router.h"

namespace route {

  Match Route::set(const std::string& u) {
    url = u;
    path_to_regex = std::regex(path_pattern);
    Match m(*this);
    return m;
  }

  std::string Match::get(const std::string& key) {
    if (pairs.count(key)) {
      return pairs.at(key);
    }
    return "";
  }

  bool Match::test(const std::string& tmpl) {

    pairs.clear();
    Path path;
    keys = 0;

    if (route->cache.count(tmpl)) {
      path = route->cache.at(tmpl);
    }

    else {
      //
      // get all the keys from the path.
      //
      std::sregex_token_iterator
        i(tmpl.begin(), tmpl.end(), route->path_to_regex),
        iend;

      while(i != iend) {
        std::string key = *i++;
        path.keys.push_back(key.erase(0, 1));
      }

      //
      // create a regex from the path.
      //
      auto exp = regex_replace(
        tmpl, 
        route->path_to_regex, 
        route->capture_pattern
      );
      path.re = std::regex("^" + exp + "$");
    }

    std::smatch sm_values;
    if (!regex_match(route->url, sm_values, path.re)) {
      return false;
    }
  
    if (sm_values.size() < 1) return true;

    for (auto i = 0; i < sm_values.size() - 1; i++) {
      std::string key = path.keys[i];
      pairs.insert(std::pair<std::string, std::string>(key, sm_values[i + 1]));
      keys++;
    }
    return true;
  }

} // namespace url

