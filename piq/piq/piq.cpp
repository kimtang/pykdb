// piq.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

# include <pykdb/ktopy.hpp>
# include <pykdb/pytok.hpp>

namespace python = boost::python;

// taken from http://thejosephturner.com/blog/2011/06/15/embedding-python-in-c-applications-with-boostpython-part-2/
std::string parse_python_exception() {
	PyObject* type_ptr = NULL, * value_ptr = NULL, * traceback_ptr = NULL;
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
	std::string ret("Unfetchable Python error");
	if (type_ptr != NULL) {
		python::handle<> h_type(type_ptr);
		python::str type_pstr(h_type);
		python::extract<std::string> e_type_pstr(type_pstr);
		if (e_type_pstr.check()) ret = e_type_pstr();
		else ret = "Unknown exception type";
	}

	if (value_ptr != NULL) {
		python::handle<> h_val(value_ptr);
		python::str a(h_val);
		python::extract<std::string> returned(a);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python error: ");
	}

	if (traceback_ptr != NULL) {
		python::handle<> h_tb(traceback_ptr);
		python::object tb(python::import("traceback"));
		python::object fmt_tb(tb.attr("format_tb"));
		python::object tb_list(fmt_tb(h_tb));
		python::object tb_str(python::str("\n").join(tb_list));
		python::extract<std::string> returned(tb_str);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python traceback");
	}
	return ret;
}

python::object main_module ;
python::object main_namespace ;

extern "C" __declspec(dllexport) kx::K py_initialize(kx::K x) {
	ktopy::k_to_p_map_init(); pytok::p_to_k_map_init();
	try { 
		Py_Initialize(); 
		boost::python::numpy::initialize();
		main_module = python::import("__main__");
		main_namespace = main_module.attr("__dict__");
		// python::exec("import numpy,pandas,uuid", main_namespace);

	}
	catch (python::error_already_set const&) { return kx::krr(parse_python_exception().c_str()); }
	return kx::kb(1);
};

extern "C" __declspec(dllexport) kx::K set(kx::K n_, kx::K o_) {

	if (!(n_->t == kx_KC) || (n_->t == -kx_KC)) { return kx::krr("type"); }
	// kx::CP str_ = kx::conv(n_);
	// std::string str(str_.first, str_.second);
	python::str n = ktopy::k_to_python_str(n_);
	python::object o;
	try {
		o = ktopy::k_to_python_map_func(o_, main_namespace);
	}
	catch (boost::python::error_already_set const&) {
		// Parse and output the exception
		std::string perror_str = parse_python_exception();
		std::cout << "Error in Python: " << perror_str << std::endl;
		return kx::krr(perror_str.c_str());
	}
	main_namespace[n] = o;
	// boost::python::scope().attr(str.c_str()) = o;

	return kx::r1(n_);
}

extern "C" __declspec(dllexport) kx::K get(kx::K n_) {
	python::str n = ktopy::k_to_python_str(n_);
	python::object o;
	kx::K kresult;
	try {
		o = python::eval(n, main_namespace);
		kresult = pytok::python_to_k_map_func(o, main_namespace);
	}
	catch (boost::python::error_already_set const&) {
		// Parse and output the exception
		std::string perror_str = parse_python_exception();
		std::cout << "Error in Python: " << perror_str << std::endl;
		return kx::krr(perror_str.c_str());
	}
	return kresult;
}


extern "C" __declspec(dllexport) kx::K eval3(kx::K n_) {

	python::str n = ktopy::k_to_python_str(n_);

	python::object result;
	kx::K kresult;
	try {
		result = python::eval(n, main_namespace);
		kresult = pytok::python_to_k_map_func(result, main_namespace);
	}
	catch (boost::python::error_already_set const&) {
		// Parse and output the exception
		std::string perror_str = parse_python_exception();
		std::cout << "Error in Python: " << perror_str << std::endl;
		return kx::krr(perror_str.c_str());
	}
	return kresult;
}

extern "C" __declspec(dllexport) kx::K exec3(kx::K n_) {


	python::str n = ktopy::k_to_python_str(n_);

	python::object result;
	kx::K kresult;
	try {
		result = python::exec(n, main_namespace);
		kresult = pytok::python_to_k_map_func(result, main_namespace);
	}
	catch (boost::python::error_already_set const&) {
		// Parse and output the exception
		std::string perror_str = parse_python_exception();
		std::cout << "Error in Python: " << perror_str << std::endl;
		return kx::krr(perror_str.c_str());
	}

	return kresult;
}



// C:\Users\kuent\AppData\Local\conda\conda\envs\torch36\include