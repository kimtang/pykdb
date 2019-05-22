
# ifndef KTOPY_HPP_KKT_22_05_2019
# define KTOPY_HPP_KKT_22_05_2019

# include <kdb/kx.hpp>
# include <boost/python.hpp>
# include <cstdint>
# include <map>
# include <string>
# include <iostream>

namespace python = boost::python;

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
		std::string sstr(k->s); return python::str(sstr);};

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
	//  kx::U* uuid = (kx::U*) k->G0;
	//  char u[37] = {};
	//  sprintf(u,"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
	//    uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7],
	//    uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
	//  );
	  return python::str("nyi");
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
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::str("bool")
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::G* g0 = k_->G0;
		for(std::size_t i=0,end = k_->n;i<end;++i,++g0)np[i ]= static_cast<bool>(*g0);
		return np;
	};
	// TODO: Add implementation for guid
	python::object lguid_to_python(kx::K k,python::object g){return python::object("nyi");};


	python::object lbyte_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::str("int8")
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::G* g0 = k_->G0;
		for(std::size_t i=0,end = k_->n;i<end;++i,++g0)np[i]= *g0;
		return np;
	};

	python::object lshort_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::str("int16")
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		std::size_t i = 0;
		for(kx::HP k = kx::conv(k_);k.first!=k.second;++k.first,++i)np[i]=*k.first;
		return np;
	};

	python::object lint_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::eval("numpy.int32",g)
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
	};
	python::object llong_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::eval("numpy.int64",g)
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::JP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
		};
	python::object lreal_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::eval("numpy.float32",g)
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::EP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
	};

	python::object lfloat_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::eval("numpy.float64",g)
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::FP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
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
		return lst;
	};

	python::object ltimestamp_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::str("datetime64[ns]")
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::JP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = kx::up(*k.first);
		return np;
	};

	python::object lmonth_to_python(kx::K k_,python::object g){
		python::object ones = python::eval("numpy.ones",g)
					  ,dtype = python::str("datetime64[M]")
					  ,size = python::object(k_->n);
		python::object np = ones(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = kx::um(*k.first);
		return np;
	};
	python::object ldate_to_python(kx::K k_,python::object g){
		python::object datetime64 = python::eval("numpy.ones",g)
					  ,dtype("datetime64[D]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = datetime64(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = kx::ud(*k.first);
		return np;
	};

	python::object ldatetime_to_python(kx::K k_,python::object g){
		python::object datetime64 = python::eval("numpy.ones",g)
					  ,dtype("datetime64[us]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = datetime64(size,dtype);
		kx::FP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = kx::uz(*k.first);
		return np;
	};
	python::object ltimespan_to_python(kx::K k_,python::object g){
		python::object timedelta64 = python::eval("numpy.ones",g)
					  ,dtype("timedelta64[ns]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = timedelta64(size,dtype);
		kx::JP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
	};
	python::object lminute_to_python(kx::K k_,python::object g){
		python::object timedelta64 = python::eval("numpy.ones",g)
					  ,dtype("timedelta64[m]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = timedelta64(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
	};
	python::object lsecond_to_python(kx::K k_,python::object g){
		python::object timedelta64 = python::eval("numpy.ones",g)
					  ,dtype("timedelta64[s]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = timedelta64(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
	};
	python::object ltime_to_python(kx::K k_,python::object g){
		python::object timedelta64 = python::eval("numpy.ones",g)
					  ,dtype("timedelta64[ms]")
					  ,size(k_->n);
		// 10957+k->i
		python::object np = timedelta64(size,dtype);
		kx::IP k = kx::conv(k_);
		for(std::size_t i = 0;k.first!=k.second;++i,++k.first)np[i] = *k.first;
		return np;
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
		return k_to_python_funcs[o->t](o, g);
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