#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;

int readJson(pt::ptree& root)
{
	// Read values
	int height = root.get<int>("height", 0);
	// You can also go through nested nodes
	std::string msg = root.get<std::string>("some.complex.path");

	// A vector to allow storing our animals
	std::vector< std::pair<std::string, std::string> > animals;

	// Iterator over all animals
	for (pt::ptree::value_type &animal : root.get_child("animals"))
	{
		// Animal is a std::pair of a string and a child

		// Get the label of the node
		std::string name = animal.first;
		// Get the content of the node
		std::string color = animal.second.data();
		animals.push_back(std::make_pair(name, color));
	    std::cout << "animal: " << animal.first << animal.second.data() << std::endl;
	}
	std::vector< std::pair<std::string, std::string> >::iterator itr;
    for (itr = animals.begin(); itr != animals.end(); ++itr) {
        std::cout << "animals: " << itr->first << itr->second.data() << std::endl;
    }

	std::vector<std::string> fruits;
	for (pt::ptree::value_type &fruit : root.get_child("fruits"))
	{
		// fruit.first contain the string ""
		fruits.push_back(fruit.second.data());
	}
    std::vector<std::string>::iterator itr2;
   for (itr2 = fruits.begin(); itr2 != fruits.end(); ++itr2) {
        std::cout << "fruits: " << itr2->c_str() << std::endl;
    }
	return 0;
}

int main()
{
	// Create a root
	pt::ptree root;

	// Load the json file in this ptree
	pt::read_json("s.json", root);

    readJson(root);
#if 0	
    BOOST_FOREACH(ptree::value_type & framePair2, root.get_child("array")) {
        auto id = framePair2.second.get_optional<std::string>("id");
        if (id && !id->compare("stackoverflow")) {
            std::cout << framePair2.second.get<std::string>("id")      << std::endl;
            std::cout << framePair2.second.get<std::string>("visible") << std::endl;
            framePair2.second.put<std::string>("visible", "false");
            std::cout  << framePair2.second.get<std::string>("visible") << std::endl;
        }
    }
#endif
	//pt::ptree::value_type &fruit = root.get_child("fruits");

    std::vector<std::string> fruits = {"mango", "banana"};
	// A vector to allow storing our animals
	//std::vector< std::pair<std::string, std::string> > animals;

    auto &f1 = fruits;
	// Iterator over all animals
	for (pt::ptree::value_type &fruit : root.get_child("fruits"))
	{
	for (pt::ptree::value_type &animal : root.get_child("animals"))
	{
		// Animal is a std::pair of a string and a child

		// Get the label of the node
		//std::string name = animal.first;
		// Get the content of the node
		//std::string color = animal.second.data();
		fruit.second = animal.second;
		fruit.second.set = f1;
		//animals.push_back(std::make_pair(name, color));
	    //std::cout << "animal: " << animal.first << animal.second.data() << std::endl;
	}
	}

	//for (pt::ptree::value_type &fruit : root.get_child("fruits"))
	{
		// fruit.first contain the string ""
		//fruit.second = animals[0];
	}

#if 0
	for (auto &fruit : fruits)
	{
		//pt::ptree fruit_node;
		root.put("fruits", fruits);

		//root.push_back(std::make_pair("", fruit_node));
		//root.put_child("fruits", fruit.c_str());
	}
	//root.push_back("fruits", "test");


	pt::ptree fruits_node;
	for (auto &fruit : fruits)
	{
		// Create an unnamed node containing the value
		pt::ptree fruit_node;
		fruit_node.put("", fruit);

		// Add this node to the list.
		fruits_node.push_back(std::make_pair("", fruit_node));
	}

	root.add_child("fruits", fruits_node);
#endif
    pt::write_json(std::cout, root);

	return 0;
}