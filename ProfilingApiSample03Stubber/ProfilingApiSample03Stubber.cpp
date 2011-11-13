// ProfilingApiSample03Stubber.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &v)
{
    using namespace std;
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;
    using namespace boost::program_options;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;
    
    options_description desc("Allowed options");
    desc.add_options()
        ("input", value<vector<string>>(), "stubbing files")
    ;
    
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (!vm.count("input"))
        return 0;
    
    vector<string> const &inputs = vm["input"].as<vector<string>>();
    cout << "Input files are: " << inputs << endl;
    
    
	return 0;
}

