
# include <pykdb/ktopy.hpp>
# include <pykdb/pytok.hpp>

using namespace boost::python;

kx::K execute0(kx::I i, kx::SS s){ return kx::k(i, s, (kx::K)0); }
kx::K execute1(kx::I i, kx::SS s,python::object k1){ return kx::k(i, s, pytok::python_to_k_map_func(k1), (kx::K)0); }
kx::K execute2(kx::I i, kx::SS s,python::object k1,python::object k2){ return kx::k(i, s, pytok::python_to_k_map_func(k1), pytok::python_to_k_map_func(k2), (kx::K)0); }
kx::K execute3(kx::I i, kx::SS s,python::object k1,python::object k2,python::object k3){ return kx::k(i, s, pytok::python_to_k_map_func(k1), pytok::python_to_k_map_func(k2), pytok::python_to_k_map_func(k3), (kx::K)0); }
kx::K execute4(kx::I i, kx::SS s,python::object k1,python::object k2,python::object k3,python::object k4){ return kx::k(i, s, pytok::python_to_k_map_func(k1), pytok::python_to_k_map_func(k2), pytok::python_to_k_map_func(k3), pytok::python_to_k_map_func(k4), (kx::K)0); }
kx::K execute5(kx::I i, kx::SS s,python::object k1,python::object k2,python::object k3,python::object k4,python::object k5){ return kx::k(i, s, pytok::python_to_k_map_func(k1), pytok::python_to_k_map_func(k2), pytok::python_to_k_map_func(k3), pytok::python_to_k_map_func(k4),pytok::python_to_k_map_func(k5), (kx::K)0); }

kx::K execute_(kx::I i, kx::SS s, python::object k1, python::object k2, python::object k3, python::object k4, python::object k5){
	if (k1 == boost::python::api::object() ) return execute0(i,s);
	if (k2 == boost::python::api::object() ) return execute1(i,s,k1);
	if (k3 == boost::python::api::object() ) return execute2(i,s,k1,k2);
	if (k4 == boost::python::api::object() ) return execute3(i,s,k1,k2,k3);
	if (k5 == boost::python::api::object() ) return execute4(i,s,k1,k2,k3,k4);
	return execute5(i,s,k1,k2,k3,k4,k5);
}

python::object execute(kx::I i, kx::SS s, python::object k1 = python::object(), python::object k2 = python::object(), python::object k3 = python::object(), python::object k4 = python::object(), python::object k5 = python::object()) {
	kx::K r = execute_(i,s,k1,k2,k3,k4,k5);

	if(r==0){
		PyErr_SetString(PyExc_ValueError, "not connected");
		python::throw_error_already_set();		
		return python::object();
	}

	if(i<0){ return python::object(); }

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
	pytok::p_to_k_map_init();
	def("execute", execute, execute_overloads());
	def("open_connection", open_connection, open_connection_overloads());
	def("close", kx::kclose);

}


int main() { return 1; }
