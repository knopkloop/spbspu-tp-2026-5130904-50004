#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <limits>
#include <stdexcept>
#include "shapes.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace haliullin;
  using namespace std::placeholders;
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  data_t polygons;
  try
  {
    polygons = readPolygonsFromFile(argv[1]);
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  std::map< std::string, cf_t > cmds;
  cmds["AREA"] = std::bind(area, _1, _2, std::cref(polygons));
  cmds["MAX"] = std::bind(max, _1, _2, std::cref(polygons));
  cmds["MIN"] = std::bind(min, _1, _2, std::cref(polygons));
  cmds["COUNT"] = std::bind(count, _1, _2, std::cref(polygons));
  cmds["INTERSECTIONS"] = std::bind(intersections, _1, _2, std::cref(polygons));
  cmds["RIGHTSHAPES"] = std::bind(rightshapes, _1, _2, std::cref(polygons));

  std::string command;
  while (std::cin >> command)
  {
    auto it = cmds.find(command);
    if (it != cmds.end())
    {
      try
      {
        it->second(std::cin, std::cout);
      }
      catch(const std::logic_error& e)
      {
        std::cout << e.what() << "\n";
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
