#include <iostream> 
#include <string>       // std::string
#include <sstream>      // std::stringstream

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using namespace std; 

class cConfig
{

public:

private:
    /**
     *  @brief
     *   Constructor/Destructor
    */

    template<typename T>
    bool SetValue(const std::string& path,
                  const T& value)
    {
        printf("enter");

        try
        {
            m_oPTreeConf.put<T>(path, value);
        }
        catch(const boost::property_tree::ptree_bad_path& pbpe)
        {
            printf("Error Set value '{}' of type '{}'; Error message : {}\n", value, typeid(T).name(), pbpe.what());
            return false;
        }
        catch(const boost::property_tree::ptree_bad_data& pbde)
        {
            printf("Error Set value '{}' of type '{}'; Error message : {}\n", value, typeid(T).name(), pbde.what());
            return false;
        }

        printf("exit");
        return true;
    }

    template<typename T>
    const T GetValue(const std::string& path, const T xDefaultValue = {})
    {
        T val;

        try
        {
            val = cConfig::GetInstance().Ptree().get<T>(path);
        }
        catch(const boost::property_tree::ptree_bad_path& pbpe)
        {
            printf("Error Get value from path '{}' of type '{}'; Error message : {}\n", path, typeid(T).name(), pbpe.what());
            return xDefaultValue;
        }
        catch(const boost::property_tree::ptree_bad_data& pbde)
        {
            printf("Error Get value '{}' of type '{}'; Error message : {}\n", path, typeid(T).name(), pbde.what());
            return xDefaultValue;
        }

        return val;
    }

public:
    static cConfig& GetInstance();

    /**
     *  @brief Load Json config from file content
     *   Members values
    */
    bool LoadConfigFromFile(const std::string& jsonFilepath);

    /**
     *  @brief Load Json config from string
     *  Members values
     */
    bool LoadConfig(const std::string& jsonString);

    /**
     *  @brief
     *   Members values
    */
    boost::property_tree::ptree& Ptree();

    boost::property_tree::ptree GetSubTree(const std::string& path);

private:
   std::string  m_oFileConfig;
   std::string  m_oFlavorConfigFilePath;
   boost::property_tree::ptree m_oPTreeConf;
};

cConfig& cConfig::GetInstance()
{
    static cConfig instance;
    return instance;
}

bool cConfig::LoadConfigFromFile (const std::string &xoJsonConfigFilePath)
{
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;

    std::ifstream ifs;
    std::stringstream        oStreamConfig;

    printf("%s %d\n", __FUNCTION__, __LINE__);

    if ( !xoJsonConfigFilePath.empty() )
    {
      m_oFileConfig = xoJsonConfigFilePath;
    }

    if ( !m_oFileConfig.empty() )
    {
        cout << "Try to load '{}'\n" << m_oFileConfig.c_str();
        ifs.open(m_oFileConfig, std::ifstream::in);
        if (ifs.is_open())
        {
          oStreamConfig << ifs.rdbuf();

          // Load config from string
          this->LoadConfig(oStreamConfig.str());

          ifs.close();
          cout << "'{}' has been loaded : '{}' " << m_oFileConfig.c_str() << oStreamConfig.str().c_str() << "\n" << endl;

          return (true);
        }
        cout << "Failed to load '{}'\n" << m_oFileConfig.c_str();
        return (false);
    }
    else
    {
      printf("Config file name is empty.");
      return (false);
    }

    return (true);
}

bool cConfig::LoadConfig(const std::string& xJsonContent)
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;

    // Create stringstream from Json string content
    std::stringstream oStreamConfig(xJsonContent);

    if ( !xJsonContent.empty() )
    {
        // Create a new tree
        // and append it to the global tree config
        // This way we can load many different file
        // and load it in the same cConfig object
        // Waring : be careful of Json merge, every component
        // must be unique in config file
        ptree newTree;
        read_json(oStreamConfig, newTree);
		ptree::iterator itr;
	/*for (itr = newTree.begin(); itr != newTree.end(); ++itr) { 
		cout << itr->second.get_value<std::string>()<< '\n'; 
	} */
        // Append the config file to the global tree
        m_oPTreeConf.insert(m_oPTreeConf.end(),
                          newTree.begin(), newTree.end());

        printf("Json content has been loaded\n");
        return (true);
    }
    else
    {
      printf("Config file name is empty.\n");
      return (false);
    }

    return (true);
}
#include <boost/property_tree/json_parser.hpp>
int main() 
{ 
#if 0
    using boost::property_tree::ptree;
    using boost::property_tree::json_parser;
  ptree pt;
  pt.put("C:.Windows.System", "20 files");
  pt.put("C:.Windows.Cursors", "50 files");

  json_parser::write_json("file.json", pt);

  ptree pt2;
  json_parser::read_json("file.json", pt2);

  std::cout << std::boolalpha << (pt == pt2) << '\n';

	ptree pt;
	pt.put("C:.Windows.System", "20 files");

	ptree &c = pt.get_child("C:.Windows");
	//ptree &windows = c.get_child("Windows");
	ptree &system = c.get_child("System");
	std::cout << system.get_value<std::string>() << '\n';
#endif
    std::string json_content_version = "{\"project_name\":\"EWC\",\"project_version\":\"0.1.2\",\"protocol\":{\"version\":\"0.1.0\",\"major\":\"0\",\"minor\":\"1\",\"patch\":\"0\"}}";

	cConfig::GetInstance().LoadConfig(json_content_version);

	cConfig::GetInstance().LoadConfigFromFile("FlavorConfig.json");

	return 0; 
} 
