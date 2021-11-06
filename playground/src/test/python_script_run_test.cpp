﻿#include "pch.h"
#include "python_script_run_test.h"

#include "base/r2_eTestResult.h"
#include "helper/r2_PythonInstance.h"

//
// # ref
// https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
//

namespace python_script_run_test
{
	r2::iTest::TitleFunc SimpleString::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "SimpleString";
		};
	}
	r2::iTest::DoFunc SimpleString::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			//
			// Python Initialize And Finalize
			//
			r2::PythonInstance python_instance;

			std::cout << r2::split;

			{
				const char* run_string = "print( \'Hello Python.\')";

				std::cout << r2::tab << "+ SimpleString" << r2::linefeed2;
				std::cout << r2::tab2 << "const char* run_string = " << run_string << ";" << r2::linefeed;
				std::cout << r2::tab2 << "PyRun_SimpleString( run_string );" << r2::linefeed;

				std::cout << r2::linefeed;

				std::cout << r2::tab3;
				std::cout << "- ";

				PyRun_SimpleString( run_string );
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc SimpleFile::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "SimpleFile";
		};
	}
	r2::iTest::DoFunc SimpleFile::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			//
			// Python Initialize And Finalize
			//
			r2::PythonInstance python_instance;

			std::cout << r2::split;

			{
				const char* script_path_string = "resources/pyscript/simplefile_test.py";

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const char* script_path_string = " << script_path_string << ";" << r2::linefeed;
				std::cout << r2::linefeed2;

				FILE* fp = nullptr;
				fopen_s( &fp, script_path_string, "r" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "FILE* fp = nullptr;" << r2::linefeed;
				std::cout << r2::tab2 << "fopen_s( &fp, script_path_string, \"r\" );" << r2::linefeed;
				std::cout << r2::linefeed2;

				if( fp )
				{
					std::cout << r2::tab << "+ Run" << r2::linefeed2;
					std::cout << r2::tab2 << "PyRun_SimpleFile( fp, script_path_string );" << r2::linefeed2;

					std::cout << r2::tab2 << "> ";
					PyRun_SimpleFile( fp, script_path_string );
					std::cout << r2::linefeed2;
				}
				else
				{
					std::cout << r2::tab << "Failed : File Open" << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}
