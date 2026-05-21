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
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  haliullin::data_t polygons;
  try
  {
    polygons = haliullin::readPolygonsFromFile(argv[1]);
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  using namespace std::placeholders;
  std::map< std::string, haliullin::cf_t > cmds;
  cmds["AREA"] = std::bind(haliullin::area, _1, _2, std::cref(polygons));
  cmds["MAX"] = std::bind(haliullin::max, _1, _2, std::cref(polygons));
  cmds["MIN"] = std::bind(haliullin::min, _1, _2, std::cref(polygons));
  cmds["COUNT"] = std::bind(haliullin::count, _1, _2, std::cref(polygons));
  cmds["INTERSECTIONS"] = std::bind(haliullin::intersections, _1, _2, std::cref(polygons));
  cmds["RIGHTSHAPES"] = std::bind(haliullin::rightshapes, _1, _2, std::cref(polygons));

  std::string command;
  while (std::cin >> command)
  {
    auto it = cmds.find(command);
    if (it != cmds.end())
    {
      it->second(std::cin, std::cout);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
