
# ifndef KTOPY_HPP_KKT_22_05_2019
# define KTOPY_HPP_KKT_22_05_2019

# include <kdb/kx.hpp>
# include <boost/python.hpp>
# include "boost/python/numpy.hpp"
# include <boost/uuid/uuid.hpp>
# include <boost/uuid/uuid_io.hpp>
# include <cstdint>
# include <map>
# include <string>
# include <iostream>

namespace python = boost::python;
namespace np = boost::python::numpy;

namespace ktopy {

	std::string parse_python_exception() {
    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
    std::string ret("Unfetchable Python error");
    if (type_ptr != NULL) {
        python::handle<> h_type(type_ptr);
        python::str type_pstr(h_type);
        python::extract<std::string> e_type_pstr(type_pstr);
        if(e_type_pstr.check()) ret = e_type_pstr();
        else ret = "Unknown exception type";
    }

    if (value_ptr != NULL) {
        python::handle<> h_val(value_ptr);
        python::str a(h_val);
        python::extract<std::string> returned(a);
        if(returned.check())
            ret +=  ": " + returned();
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
        if(returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;}

	python::object k_to_python_map_func(kx::K, python::object);

	python::object time_to_python(kx::K k,python::object g){
		python::object timedelta64 = python::eval("numpy.timedelta64",g)
					  ,dtype("ms")
					  ,value(k->i);
		python::object r = timedelta64 (value,dtype);
		return r;
	};
	python::object second_to_python(kx::K k,python::object g){
		python::object timedelta64 = python::eval("numpy.timedelta64",g)
					  ,dtype("s")
					  ,value(k->i);
		python::object r = timedelta64 (value,dtype);
		return r;
	};
	python::object minute_to_python(kx::K k,python::object g){
		python::object timedelta64 = python::eval("numpy.timedelta64",g)
					  ,dtype("m")
					  ,value(k->i);
		python::object r = timedelta64 (value,dtype);
		return r;
	};
	python::object timespan_to_python(kx::K k,python::object g){
		python::object timedelta64 = python::eval("numpy.timedelta64",g)
					  ,dtype("ns")
					  ,value(k->j);
		return timedelta64 (value,dtype);
	};
	python::object datetime_to_python(kx::K k,python::object g){
		python::object datetime64 = python::eval("numpy.datetime64",g)
					  ,dtype("us")
					  ,value(kx::uz(k->f));
		return datetime64 (value,dtype);
	};
	python::object date_to_python(kx::K k,python::object g){
		python::object datetime64 = python::eval("numpy.datetime64",g)
					  ,dtype("D")
					  ,value(10957+k->i);
		return datetime64 (value,dtype);
	};
	python::object month_to_python(kx::K k,python::object g){
		python::object datetime64 = python::eval("numpy.datetime64",g)
					  ,dtype("M")
					  ,value(kx::um(k->i));
		return datetime64 (value,dtype);
	};
	python::object timestamp_to_python(kx::K k,python::object g){
		python::object timedelta64 = python::eval("numpy.datetime64",g)
					  ,dtype("ns")
					  ,value(kx::up(k->j));
		return timedelta64(value,dtype);
	};
	// we will pass it as string. There is no way to distinguish between string and symbols
	python::object symbol_to_python(kx::K k,python::object g){
		python::object str_ = python::eval("numpy.str_", g);
		std::string sstr(k->s);
		return str_(sstr);
	};

	python::object char_to_python(kx::K k,python::object g){
		kx::C c = k->g; return python::object(c);
	};

	python::object float_to_python(kx::K k,python::object g){return python::object(k->f);};

	python::object real_to_python(kx::K k,python::object g){return python::object(k->e);};

	python::object long_to_python(kx::K k,python::object g){return python::object(k->j);};

	python::object int_to_python(kx::K k,python::object g){return python::object(k->i);};

	python::object short_to_python(kx::K k,python::object g){return python::object(k->h);};

	python::object byte_to_python(kx::K k,python::object g){ return python::object(k->g);};

	python::object guid_to_python(kx::K k,python::object g){
		kx::G* guid = ((kx::U*) k->G0)->g;	  
		
		boost::uuids::uuid u;
		std::copy(guid, guid + 16, u.begin());
		std::string uu = boost::uuids::to_string(u);
		python::object uuid = python::eval("uuid.UUID",g)
					  ,sguid = python::str(uu);
		return uuid(sguid);
	  };

	python::object boolean_to_python(kx::K k,python::object g){
		return python::object((bool)k->g);
	 };

	python::object list_to_python(kx::K k_,python::object g){
		python::list lst = python::list();
		for(kx::KP k = kx::conv(k_);k.first!=k.second;++k.first) lst.append(k_to_python_map_func(*k.first,g) );
		return lst;
	};

	python::object lboolean_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<bool>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		bool* iter = reinterpret_cast<bool*>(na.get_data());
		kx::G* g0 = k_->G0;
		for (std::size_t i = 0, end = k_->n; i < end; ++i, ++iter, ++g0) *iter = static_cast<bool>(*g0);
		return na;
	};

	// TODO: Add implementation for guid
	python::object lguid_to_python(kx::K k,python::object g){
		python::list lst = python::list();
		kx::U* luuid = (kx::U*) k->G0;
		for(std::size_t i=0,end = k->n;i<end;++i,++luuid)
		{
	  		char u[37] = {};
	  		kx::G* guid = luuid->g;
	  		sprintf_s(u,"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
	    		guid[0], guid[1], guid[2], guid[3], guid[4], guid[5], guid[6], guid[7],
	    		guid[8], guid[9], guid[10], guid[11], guid[12], guid[13], guid[14], guid[15]
	  		);
	  		python::object uuid = python::eval("uuid.UUID",g)
					  	 ,sguid = python::str(u);
			lst.append(uuid(sguid) );
		}

		return lst;
	};


	python::object lbyte_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::G>();

		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::G* iter = reinterpret_cast<kx::G*>(na.get_data());

		kx::G* g0 = k_->G0;
		for (kx::G* end = g0 + k_->n; g0 != end; ++g0,++iter) *iter = *g0;
		return na;

	};

	python::object lshort_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::H>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::H* iter = reinterpret_cast<kx::H*>(na.get_data());
		for (kx::HP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na;
	};

	python::object lint_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na;
	};
	python::object llong_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::J>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::J* iter = reinterpret_cast<kx::J*>(na.get_data());
		for (kx::JP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na;
		};

	python::object lreal_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::E>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::E* iter = reinterpret_cast<kx::E*>(na.get_data());
		for (kx::EP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na;
	};

	python::object lfloat_to_python(kx::K k_,python::object g){
		np::dtype dt = np::dtype::get_builtin<kx::F>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::F* iter = reinterpret_cast<kx::F*>(na.get_data());
		for(kx::FP k = kx::conv(k_);k.first!=k.second;++iter,++k.first) *iter = *k.first;
		return na;
	};

	python::object lchar_to_python(kx::K k_,python::object g){
		kx::CP k = kx::conv(k_);
		std::string str(k.first,k.second);
		return python::object(str);
	};

	python::object lsymbol_to_python(kx::K k_,python::object g){
		python::list lst;
		for(kx::SP k = kx::conv(k_);k.first!=k.second;++k.first){
			std::string str_(*k.first);
			python::str str(str_);
			lst.append(str);
		}
		return np::array(lst);
	};

	python::object ltimestamp_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::J>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::J* iter = reinterpret_cast<kx::J*>(na.get_data());
		for (kx::JP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = kx::up(*k.first);
		return na.attr("astype")("datetime64[ns]");
	};

	python::object lmonth_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = kx::um(*k.first);

		return na.attr("astype")("datetime64[M]");
	};
	python::object ldate_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = kx::ud(*k.first);

		return na.attr("astype")("datetime64[D]");
	};

	python::object ldatetime_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::F>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::F* iter = reinterpret_cast<kx::F*>(na.get_data());
		for (kx::FP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = kx::uz(*k.first);

		return na.attr("astype")("datetime64[us]");

	};
	python::object ltimespan_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::J>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::J* iter = reinterpret_cast<kx::J*>(na.get_data());
		for (kx::JP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na.attr("astype")("timedelta64[ns]");
	};
	python::object lminute_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na.attr("astype")("timedelta64[m]");

	};
	python::object lsecond_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na.attr("astype")("timedelta64[s]");

	};
	python::object ltime_to_python(kx::K k_,python::object g){

		np::dtype dt = np::dtype::get_builtin<kx::I>();
		python::tuple shape = python::make_tuple(k_->n);
		np::ndarray na = np::zeros(shape, dt);
		kx::I* iter = reinterpret_cast<kx::I*>(na.get_data());
		for (kx::IP k = kx::conv(k_); k.first != k.second; ++iter, ++k.first) * iter = *k.first;
		return na.attr("astype")("timedelta64[ms]");

	};

	python::object dict_to_python(kx::K k,python::object g){
		python::dict d;
		kx::K x = kx::conv(k)(kx::dx()); 	kx::K y = kx::conv(k)(kx::dy());

		if(x->t!=98){
			python::object dx = k_to_python_map_func(x,g);
			python::object dy = k_to_python_map_func(y,g);
			for(std::size_t i=0,end=x->n;i!=end;++i)d[dx[i]] = dy[i];
		}
		else{
			python::object df = python::eval("pandas.DataFrame",g);
			python::list lst;
			kx::K xx = kx::conv(x)(kx::tx()); 	kx::K xy = kx::conv(x)(kx::ty());
			python::object dxx = k_to_python_map_func(xx,g);
			python::object dxy = k_to_python_map_func(xy,g);
			for(std::size_t i=0,end=xx->n;i!=end;++i){
				lst.append(dxx[i]);
				d[dxx[i]] = dxy[i];
			}

			kx::K yx = kx::conv(y)(kx::tx()); 	kx::K yy = kx::conv(y)(kx::ty());
			python::object dyx = k_to_python_map_func(yx,g);
			python::object dyy = k_to_python_map_func(yy,g);
			for(std::size_t i=0,end=yx->n;i!=end;++i){
				lst.append(dyx[i]);
				d[dyx[i]] = dyy[i];
			}
			return df(d)[lst]; // .attr("set_index")(dxx);
		}
		return d;
	};

	python::object table_to_python(kx::K k,python::object g){
	  try{
		python::object df = python::eval("pandas.DataFrame",g);
		kx::K x = kx::conv(k)(kx::tx()); 	kx::K y = kx::conv(k)(kx::ty());
		python::object dx = k_to_python_map_func(x,g);
		python::object dy = k_to_python_map_func(y,g);
		python::dict d;
		for(std::size_t i=0,end=x->n;i!=end;++i)d[dx[i]] = dy[i];
		return df(d)[dx];
	  }catch(boost::python::error_already_set const &){
	        // Parse and output the exception
	    std::string perror_str = parse_python_exception();
	    std::cout << "Error in Python: " << perror_str << std::endl;
	    return python::object(perror_str );
	  }

	};

	python::object error_to_python(kx::K k,python::object g){
		char *e= kx::ss(k->s);
		kx::r0(k);
		PyErr_SetString(PyExc_ValueError, e);
		python::throw_error_already_set();
		return python::object();
	};


	typedef python::object(*k_to_python_func)(kx::K, python::object);

	typedef std::map<int, k_to_python_func>k_to_python_funcs_;

	k_to_python_funcs_ k_to_python_funcs;

	python::object k_to_python_map_func(kx::K o,python::object g = python::object()) {
		k_to_python_funcs_::iterator  i = k_to_python_funcs.find(o->t);		
		if (i == k_to_python_funcs.end()) return python::object();
		return (i->second)(o, g);
	}

	python::str k_to_python_str(kx::K e_) {
		if (e_->t > 0) {
			kx::CP e = kx::conv(e_);
			boost::python::str str(e.first, e.second);
			return str;
		}
		else {
			kx::C g = (e_)->g;
			boost::python::str str(&g, 1);
			return str;
		}
	}

	void k_to_p_map_init() {
		k_to_python_funcs[-128] = &error_to_python;		
		k_to_python_funcs[-19] = &time_to_python;
		k_to_python_funcs[-18] = &second_to_python;
		k_to_python_funcs[-17] = &minute_to_python;
		k_to_python_funcs[-16] = &timespan_to_python;
		k_to_python_funcs[-15] = &datetime_to_python;
		k_to_python_funcs[-14] = &date_to_python;
		k_to_python_funcs[-13] = &month_to_python;
		k_to_python_funcs[-12] = &timestamp_to_python;
		k_to_python_funcs[-11] = &symbol_to_python;
		k_to_python_funcs[-10] = &char_to_python;
		k_to_python_funcs[-9] = &float_to_python;
		k_to_python_funcs[-8] = &real_to_python;
		k_to_python_funcs[-7] = &long_to_python;
		k_to_python_funcs[-6] = &int_to_python;
		k_to_python_funcs[-5] = &short_to_python;
		k_to_python_funcs[-4] = &byte_to_python;
		k_to_python_funcs[-2] = &guid_to_python;
		k_to_python_funcs[-1] = &boolean_to_python;
		k_to_python_funcs[0] = &list_to_python;
		k_to_python_funcs[1] = &lboolean_to_python;
		k_to_python_funcs[2] = &lguid_to_python;
		k_to_python_funcs[4] = &lbyte_to_python;
		k_to_python_funcs[5] = &lshort_to_python;
		k_to_python_funcs[6] = &lint_to_python;
		k_to_python_funcs[7] = &llong_to_python;
		k_to_python_funcs[8] = &lreal_to_python;
		k_to_python_funcs[9] = &lfloat_to_python;
		k_to_python_funcs[10] = &lchar_to_python;
		k_to_python_funcs[11] = &lsymbol_to_python;
		k_to_python_funcs[12] = &ltimestamp_to_python;
		k_to_python_funcs[13] = &lmonth_to_python;
		k_to_python_funcs[14] = &ldate_to_python;
		k_to_python_funcs[15] = &ldatetime_to_python;
		k_to_python_funcs[16] = &ltimespan_to_python;
		k_to_python_funcs[17] = &lminute_to_python;
		k_to_python_funcs[18] = &lsecond_to_python;
		k_to_python_funcs[19] = &ltime_to_python;
		k_to_python_funcs[98] = &table_to_python;
		k_to_python_funcs[99] = &dict_to_python;
	}

} // ktopy  


# endif