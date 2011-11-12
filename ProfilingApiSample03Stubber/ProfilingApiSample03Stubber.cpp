// ProfilingApiSample03Stubber.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    using namespace std;
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;
    using namespace boost::program_options;
    
    options_description desc("Allowed options");
    desc.add_options()
        ("input", value<vector<string>>(), "stubbing files")
    ;
    
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("input"))
    {
        cout << "Input files are: " << vm["input"].as<vector<string>>() << endl;
    }    
    
	return 0;
}

