
# include <pykdb/ktopy.hpp>

using namespace boost::python;

PyObject* createExceptionClass(const char* name, PyObject* baseTypeObj = PyExc_Exception)
{
	using std::string;
	namespace bp = boost::python;

	string scopeName = bp::extract<string>(bp::scope().attr("__name__"));
	string qualifiedName0 = scopeName + "." + name;
	char* qualifiedName1 = const_cast<char*>(qualifiedName0.c_str());

	PyObject* typeObj = PyErr_NewException(qualifiedName1, baseTypeObj, 0);
	if (!typeObj) bp::throw_error_already_set();
	bp::scope().attr(name) = bp::handle<>(bp::borrowed(typeObj));
	return typeObj;
}

PyObject* myExceptionTypeObj = 0;

python::object execute(kx::I i, kx::SS s, kx::K k1 = 0, kx::K k2 = 0, kx::K k3 = 0, kx::K k4 = 0, kx::K k5 = 0) {
	kx::K r;
	if (k1 == 0) r = kx::k(i, s, (kx::K)0);
	if (k2 == 0) r = kx::k(i, s,k1, (kx::K)0);
	if (k3 == 0) r = kx::k(i, s, k1, k2, (kx::K)0);
	if (k4 == 0) r = kx::k(i, s, k1, k2, k3, (kx::K)0);
	r = kx::k(i, s, k1, k2, k3, k4, k5, (kx::K)0);

	if(r==0){
		PyErr_SetString(PyExc_ValueError, "not connected");
		python::throw_error_already_set();		
		return python::object();
	}

	if(i<0){
		return python::object();
	}

	return ktopy::k_to_python_map_func(r);

}

BOOST_PYTHON_FUNCTION_OVERLOADS(execute_overloads, execute, 2, 7)


kx::I open_connection(kx::I p, const kx::SS h = 0, const kx::SS u = 0, kx::I n = 0) {
	std::string host("");
	if (h == 0) return kx::khp(host.c_str(), p);
	if (u == 0) return kx::khp(h, p);
	if (n == 0) return kx::khpu(h, p, u);
	return kx::khpun(h, p, u, n);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(open_connection_overloads, open_connection, 1, 4)


BOOST_PYTHON_MODULE(qip)
{
	ktopy::k_to_p_map_init();

	def("execute", execute, execute_overloads());
	myExceptionTypeObj = createExceptionClass("qip error");
	def("open_connection", open_connection, open_connection_overloads());
	def("close", kx::kclose);

}


int main() { return 1; }
