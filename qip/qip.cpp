
# include <qp/qp.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(qip)
{
	class_<kx::k0, boost::noncopyable>("kx::k0")
		.def_readwrite("k0", &kx::k0::k)
		.def_readwrite("a", &kx::k0::a)
		.def_readwrite("t", &kx::k0::t)
		.def_readwrite("u", &kx::k0::u)
		.def_readwrite("r", &kx::k0::r)
		.def_readwrite("g", &kx::k0::g)
		.def_readwrite("h", &kx::k0::h)
		.def_readwrite("i", &kx::k0::i)
		.def_readwrite("j", &kx::k0::j)
		.def_readwrite("e", &kx::k0::e)
		.def_readwrite("f", &kx::k0::f)
		.def_readwrite("s", &kx::k0::s)
		.def("assignG", &qp::assign<kx::G>)
		.def("assignC", &qp::assign<kx::C>)
		.def("assignH", &qp::assign<kx::H>)
		.def("assignI", &qp::assign<kx::I>)
		.def("assignJ", &qp::assign<kx::J>)
		.def("assignE", &qp::assign<kx::E>)
		.def("assignF", &qp::assign<kx::F>)
		.def("assignS", &qp::assign<kx::S>);

	class_<qp::lG>("lG", init<kx::K>()).def("__iter__", range(&qp::lG::begin, &qp::lG::end));
	class_<qp::lC>("lC", init<kx::K>()).def("__iter__", range(&qp::lC::begin, &qp::lC::end));
	class_<qp::lH>("lH", init<kx::K>()).def("__iter__", range(&qp::lH::begin, &qp::lH::end));
	class_<qp::lI>("lI", init<kx::K>()).def("__iter__", range(&qp::lI::begin, &qp::lI::end));
	class_<qp::lJ>("lJ", init<kx::K>()).def("__iter__", range(&qp::lJ::begin, &qp::lJ::end));
	class_<qp::lE>("lE", init<kx::K>()).def("__iter__", range(&qp::lE::begin, &qp::lE::end));
	class_<qp::lF>("lF", init<kx::K>()).def("__iter__", range(&qp::lF::begin, &qp::lF::end));
	class_<qp::lS>("lS", init<kx::K>()).def("__iter__", range(&qp::lS::begin, &qp::lS::end));
	class_<qp::lK>("lK", init<kx::K>()).def("__iter__", range(&qp::lK::begin, &qp::lK::end));

	// qp
	def("n", qp::n);
	// def("G0",qp::G0);
	def("k0", qp::k0, return_value_policy<reference_existing_object>());
	def("k2", qp::k2, return_value_policy<reference_existing_object>());
	def("k3", qp::k3, return_value_policy<reference_existing_object>());
	def("k4", qp::k4, return_value_policy<reference_existing_object>());
	def("knk1", qp::knk1, return_value_policy<reference_existing_object>());
	def("knk2", qp::knk2, return_value_policy<reference_existing_object>());
	def("knk3", qp::knk3, return_value_policy<reference_existing_object>());
	def("knk4", qp::knk4, return_value_policy<reference_existing_object>());

	def("sn", qp::sn);
	def("ss", qp::ss);

	// def("ktj",qp::ktj);
	def("ka", kx::ka, return_value_policy<reference_existing_object>());
	def("kb", kx::kb, return_value_policy<reference_existing_object>());
	def("kg", kx::kg, return_value_policy<reference_existing_object>());
	def("kh", kx::kh, return_value_policy<reference_existing_object>());
	def("ki", kx::ki, return_value_policy<reference_existing_object>());
	def("kj", kx::kj, return_value_policy<reference_existing_object>());
	def("ke", kx::ke, return_value_policy<reference_existing_object>());
	def("kf", kx::kf, return_value_policy<reference_existing_object>());
	def("kc", kx::kc, return_value_policy<reference_existing_object>());
	def("ks", kx::ks, return_value_policy<reference_existing_object>());
	def("kd", kx::kd, return_value_policy<reference_existing_object>());
	def("kz", kx::kz, return_value_policy<reference_existing_object>());
	def("kt", kx::kt, return_value_policy<reference_existing_object>());
	def("kp", kx::kp, return_value_policy<reference_existing_object>());
	// def("krr",qp::krr);
	// def("orr",qp::orr);

	def("xD", kx::xD, return_value_policy<reference_existing_object>());
	def("xT", kx::xT, return_value_policy<reference_existing_object>());
	def("ktd", kx::ktd, return_value_policy<reference_existing_object>());
	def("ktn", kx::ktn, return_value_policy<reference_existing_object>());

	// qp
	def("khpun", kx::khpun);
	def("khpu", kx::khpu);
	def("khp", kx::khp);
	def("ymd", kx::ymd);
	def("dj", kx::dj);

	def("r0", kx::r0);
	def("r1", kx::r1, return_value_policy<reference_existing_object>());
	def("b9", kx::b9, return_value_policy<reference_existing_object>());
	def("d9", kx::d9, return_value_policy<reference_existing_object>());
	// def("dot",kx::dot,return_value_policy<reference_existing_object>());
	// def("krr",kx::krr,return_value_policy<reference_existing_object>());
	// def("orr",kx::orr,return_value_policy<reference_existing_object>());


	def("kclose", kx::kclose);
	// def("sd0",kx::sd0);
	def("m9", kx::m9);
}


int main() { return 1; }
