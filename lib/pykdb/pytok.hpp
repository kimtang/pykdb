
# ifndef PYKTO_HPP_KKT_22_05_2019
# define PYKTO_HPP_KKT_22_05_2019

# include <kdb/kx.hpp>
# include <boost/python.hpp>
# include <cstdint>
# include <map>
# include <string>
# include <iostream>

namespace python = boost::python;

namespace pytok {

	typedef kx::K(*python_to_k_func)(python::object,python::object,python::object);

	typedef std::map<std::string,python_to_k_func>python_to_k_funcs_;

	python_to_k_funcs_ python_to_k_funcs;

	std::string python_name(python::object const&o){
		python::object oo = o.attr("__class__").attr("__name__");
		std::string str = python::extract<std::string>(oo);
		return python::extract<std::string>(oo);
	}

	kx::K python_to_k_map_func(python::object ,python::object ,python::object );

	kx::K timedelta64_ms_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::kt(python::extract<kx::I>(o_));
	}

	kx::K timedelta64_s_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::ktj(-18,python::extract<kx::I>(o_));
	}


	kx::K timedelta64_m_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::ktj(-17,python::extract<kx::I>(o_));
	}

	kx::K timedelta64_ns_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("long",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::ktj(-16,python::extract<kx::J>(o_));
	}

	kx::K datetime64_us_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("long",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		// return kx::kf(kx::zu(python::extract<kx::J>(o_)));
		return kx::kz(kx::zu(python::extract<kx::J>(o_)));
	}

	kx::K datetime64_d_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::kd(python::extract<kx::I>(o_) - 10957 );
	}

	kx::K datetime64_M_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		return kx::ktj(-13,kx::mu(python::extract<kx::J>(o_)));
	}

	kx::K datetime64_ns_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("long",g,l);
		python::object o_ = lng(o.attr("astype")(lng));
		// return kx::kf(kx::zu(python::extract<kx::J>(o_)));
		return kx::ktj(-12,kx::pu(python::extract<kx::J>(o_)));
	}

	kx::K bool_to_kdb(python::object o,python::object g,python::object l){
		return kx::kb((bool) python::extract<bool>(o));
	}

	kx::K list_to_kdb(python::object o,python::object g,python::object l){
		python::list lst = python::extract<python::list>(o);
		std::size_t len = python::len(lst);
		kx::K k_ = kx::ktn(0,len);
		kx::K* k = kx::conv(k_);
		for(std::size_t i=0;i!=len;++i) k[i] = python_to_k_map_func(lst[i],g,l);
		return k_;
	};

	kx::K bool_ndarray_to_kdb(python::object o_,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o_.attr("size"));
		python::object o = o_.attr("item");
		kx::K r_ = kx::ktn(1,size);
		std::size_t i = 0;
		kx::G* r = r_->G0;
		for(std::size_t i = 0;i!=size;++r,++i) (*r) = (bool)python::extract<bool>(o(i));
		return r_;
	}

	kx::K int_to_kdb(python::object o,python::object g,python::object l){return kx::ki(python::extract<int>(o));};
	kx::K float_to_kdb(python::object o,python::object g,python::object l){return kx::kf(python::extract<double>(o));};
	kx::K long_to_kdb(python::object o,python::object g,python::object l){return kx::kj(python::extract<long>(o));};

	kx::K str_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("__len__")());
		char const* c_str = python::extract<char const*>(o);
		kx::K r_ = kx::ktn(10,size);
		for(kx::CP r = kx::conv(r_);r.first!=r.second;++r.first,++c_str) *r.first = *c_str;
		return r_;
	};

	kx::K ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::string n = python::extract<std::string>(o.attr("dtype").attr("name"));
		n.append("_ndarray");
		python_to_k_funcs_::iterator i =  python_to_k_funcs.find(n);
		if(i == python_to_k_funcs.end() ) return kx::krr(kx::ss(n.c_str())); // string is not shown, fix it
		return (i->second)(o,g,l);
	}

	kx::K int8_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(4,size);
		std::size_t i = 0;
		python::object oo = o.attr("item");
		for(kx::GP r = kx::conv(r_);r.first!=r.second;++r.first,++i) *r.first = (kx::I) python::extract<kx::I>(oo(i));
		return r_;
	}

	kx::K int16_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(5,size);
		std::size_t i = 0;
		for(kx::HP r = kx::conv(r_);r.first!=r.second;++r.first,++i) *r.first = python::extract<kx::H>(o[i]);
		return r_;
	}

	kx::K int32_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(6,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i) *r.first = python::extract<kx::I>(o[i]);
		return r_;
	}

	kx::K int64_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(7,size);
		std::size_t i = 0;
		for(kx::JP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::J>(o[i].attr("item")());
		return r_;
	}

	kx::K float32_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(8,size);
		std::size_t i = 0;
		for(kx::EP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::E>(o[i].attr("item")());
		return r_;
	}

	kx::K float64_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(9,size);
		std::size_t i = 0;
		for(kx::FP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::F>(o[i].attr("item")());
		return r_;
	}

	kx::K timedelta64_ns_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(16,size);
		std::size_t i = 0;
		for(kx::JP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::J>(o[i].attr("item")());
		return r_;
	}

	kx::K datetime64_M_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object integer = python::eval("int",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(13,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = kx::mu( python::extract<kx::I>(o[i].attr("astype")(integer))) ;
		return r_;
	}

	kx::K datetime64_D_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object integer = python::eval("int",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(14,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = kx::du( python::extract<kx::I>(o[i].attr("astype")(integer))) ;
		return r_;
	}

	kx::K datetime64_us_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("long",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(15,size);
		std::size_t i = 0;
		for(kx::FP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = kx::zu( python::extract<kx::J>(lng(o[i].attr("astype")(lng)))) ;
		return r_;
	}

	kx::K datetime64_ns_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("long",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(12,size);
		std::size_t i = 0;
		for(kx::JP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = kx::pu(python::extract<kx::J>(lng(o[i].attr("astype")(lng)))) ;
		return r_;
	}

	kx::K timedelta64_ms_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object lng = python::eval("int",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(19,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::I>(lng(o[i].attr("astype")(lng)));
		return r_;
	}

	kx::K timedelta64_m_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object integ = python::eval("int",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(17,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::I>(integ(o[i].attr("astype")(integ))) ;
		return r_;
	}

	kx::K timedelta64_s_ndarray_to_kdb(python::object o,python::object g,python::object l){
		python::object integ = python::eval("int",g);
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(18,size);
		std::size_t i = 0;
		for(kx::IP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python::extract<kx::I>(integ(o[i].attr("astype")(integ))) ;
		return r_;
	}

	kx::K object_ndarray_to_kdb(python::object o,python::object g,python::object l){
		std::size_t size = python::extract<std::size_t>(o.attr("size"));
		kx::K r_ = kx::ktn(0,size);
		std::size_t i = 0;
		for(kx::KP r = kx::conv(r_);r.first!=r.second;++r.first,++i)*r.first = python_to_k_map_func(o[i],g,l);
		return r_;
	}



	kx::K numpy_to_kdb(python::object o,python::object g,python::object l){
		std::string n = python::extract<std::string>(o.attr("dtype").attr("name"));
		python_to_k_funcs_::iterator i =  python_to_k_funcs.find(n);
		if(i == python_to_k_funcs.end() ) return kx::krr(kx::ss(n.c_str())); // string is not shown, fix it
		return (i->second)(o,g,l);
	}


	kx::K dict_to_kdb(python::object o,python::object g,python::object l){
		python::dict d = python::extract<python::dict>(o);
		python::list dk = d.keys();
		std::size_t size = python::len(dk),i=0;
		kx::K k = kx::ktn(11,size);
		for(kx::SP s = kx::conv(k);s.first!=s.second;++s.first,++i){
			std::string str = python::extract<std::string >(dk[i]);
			*s.first = kx::ss(str.c_str());
		}
		kx::K v = python_to_k_map_func (d.values(),g,l);
		return kx::xD(k,v);
	};

	kx::K dataFrame_to_kdb(python::object o,python::object g,python::object l){
		python::list columns = python::extract<python::list>(o.attr("columns").attr("tolist")());
		std::size_t size = python::len(columns),i = 0;
		kx::K symbol= kx::ktn(11,size);
		for(kx::SP s = kx::conv(symbol);s.first!=s.second;++s.first,++i){
			std::string str = python::extract<std::string >(columns[i]);
			*s.first = kx::ss(str.c_str());
		}

		kx::K values= kx::ktn(0,size);
		i=0;

		for(kx::KP v = kx::conv(values);v.first!=v.second;++v.first,++i){
			*v.first = python_to_k_map_func(o[ columns[i] ].attr("values"),g,l);
		}
		// kx::K kd = python_to_k_map_func (dict,g,l);
		return kx::xT(kx::xD(symbol,values));
	};



	kx::K nonetype_to_kdb(python::object o,python::object g,python::object l){return kx::ktn(0,0);};

	void p_to_k_map_init(){
	  python_to_k_funcs["int"] = &int_to_kdb;
	  python_to_k_funcs["float"] = &float_to_kdb;
	  python_to_k_funcs["long"] = &long_to_kdb;
	  python_to_k_funcs["str"] = &str_to_kdb;

	  python_to_k_funcs["timedelta64"] = &numpy_to_kdb;
	  python_to_k_funcs["datetime64"] = &numpy_to_kdb;

	  python_to_k_funcs["datetime64[D]"] = &datetime64_d_to_kdb;
	  python_to_k_funcs["timedelta64[ms]"] = &timedelta64_ms_to_kdb;
	  python_to_k_funcs["timedelta64[s]"] = &timedelta64_s_to_kdb;
	  python_to_k_funcs["timedelta64[m]"] = &timedelta64_m_to_kdb;
	  python_to_k_funcs["timedelta64[ns]"] = &timedelta64_ns_to_kdb;
	  python_to_k_funcs["datetime64[us]"] = &datetime64_us_to_kdb;
	  python_to_k_funcs["datetime64[M]"] = &datetime64_M_to_kdb;
	  python_to_k_funcs["datetime64[ns]"] = &datetime64_ns_to_kdb;

	  python_to_k_funcs["ndarray"] = &ndarray_to_kdb;
	  python_to_k_funcs["int8_ndarray"] = &int8_ndarray_to_kdb;
	  python_to_k_funcs["int32_ndarray"] = &int32_ndarray_to_kdb;
	  python_to_k_funcs["int64_ndarray"] = &int64_ndarray_to_kdb;
	  python_to_k_funcs["float32_ndarray"] = &float32_ndarray_to_kdb;
	  python_to_k_funcs["float64_ndarray"] = &float64_ndarray_to_kdb;

	  python_to_k_funcs["datetime64[ns]_ndarray"] = &datetime64_ns_ndarray_to_kdb;
	  python_to_k_funcs["datetime64[M]_ndarray"] = &datetime64_M_ndarray_to_kdb;
	  python_to_k_funcs["datetime64[D]_ndarray"] = &datetime64_D_ndarray_to_kdb;
	  python_to_k_funcs["datetime64[us]_ndarray"] = &datetime64_us_ndarray_to_kdb;
	  python_to_k_funcs["timedelta64[ns]_ndarray"] = &timedelta64_ns_ndarray_to_kdb;
	  python_to_k_funcs["timedelta64[m]_ndarray"] = &timedelta64_m_ndarray_to_kdb;
	  python_to_k_funcs["timedelta64[s]_ndarray"] = &timedelta64_s_ndarray_to_kdb;
	  python_to_k_funcs["timedelta64[ms]_ndarray"] = &timedelta64_ms_ndarray_to_kdb;
	  python_to_k_funcs["object_ndarray"] = &object_ndarray_to_kdb;

	  python_to_k_funcs["bool_ndarray"] = &bool_ndarray_to_kdb;

	  python_to_k_funcs["bool"] = &bool_to_kdb;

	  // python_to_k_funcs["lsymbol_enum_meta"] = &symbol_enum_meta_to_kdb;

	  python_to_k_funcs["list"] = &list_to_kdb;
	  python_to_k_funcs["dict"] = &dict_to_kdb;
	  python_to_k_funcs["DataFrame"] = &dataFrame_to_kdb;
	  python_to_k_funcs["NoneType"] = &nonetype_to_kdb;
	  }

	kx::K python_to_k_map_func(python::object o_,python::object g = python::object(),python::object l= python::object()){
		std::string n = python_name(o_);
		python_to_k_funcs_::iterator i =  python_to_k_funcs.find(n);
		// if(i == python_to_k_funcs.end() )return object_map_put(o_);
		return (i->second)(o_,g,l);
	}


}

# endif