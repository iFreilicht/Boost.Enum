
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/enum/define.hpp>
#include <boost/enum/options.hpp>

//#define BOOST_TEST_MAIN
//#include <boost/test/unit_test.hpp>

#include <iostream>

using boost::enum_::options;
using boost::enum_::option_vals;

enum class leg_scoped {
	zero, one, two, ten = 10
};

BOOST_ENUM_DEFINE_W_OPTIONS(ben_scoped,
	(options<option_vals::use_default>),
	(zero)
	(one)
	(two)
	(ten, (10))
);

BOOST_ENUM_DEFINE(Many,
	(a) (b) (c) (d) (e) (f) (g) (h) (i) (j) (k) (l) (m) (n) (o) (p) (q) (r) (s) (t) (u) (v) (w) (x) (y) (z)
	(Aa)(Ab)(Ac)(Ad)(Ae)(Af)(Ag)(Ah)(Ai)(Aj)(Ak)(Al)(Am)(An)(Ao)(Ap)(Aq)(Ar)(As)(At)(Au)(Av)(Aw)(Ax)(Ay)(Az)
	(Ba)(BB)(Bc)(Bd)(Be)(Bf)(Bg)(Bh)(Bi)(Bj)(Bk)(Bl)(Bm)(Bn)(Bo)(Bp)(Bq)(Br)(Bs)(Bt)(Bu)(Bv)(Bw)(Bx)(By)(Bz)
	(Ca)(Cb)(Cc)(Cd)(Ce)(Cf)(Cg)(Ch)(Ci)(Cj)(Ck)(Cl)(Cm)(Cn)(Co)(Cp)(Cq)(Cr)(Cs)(Ct)(Cu)(Cv)(Cw)(Cx)(Cy)(Cz)
	(Da)(Db)(Dc)(Dd)(De)(Df)(Dg)(Dh)(Di)(Dj)(Dk)(Dl)(Dm)(Dn)(Do)(Dp)(Dq)(Dr)(Ds)(Dt)(Du)(Dv)(Dw)(Dx)(Dy)(Dz)
	(Ea)(Eb)(Ec)(Ed)(Ee)(Ef)(Eg)(Eh)(Ei)(Ej)(Ek)(El)(Em)(En)(Eo)(Ep)(Eq)(Er)(Es)(Et)(Eu)(Ev)(Ew)(Ex)(Ey)(Ez)
	(Fa)(Fb)(Fc)(Fd)(Fe)(Ff)(Fg)(Fh)(Fi)(Fj)(Fk)(Fl)(Fm)(Fn)(Fo)(Fp)(Fq)(Fr)(Fs)(Ft)(Fu)(Fv)(Fw)(Fx)(Fy)(Fz)
	(Ga)(Gb)(Gc)(Gd)(Ge)(Gf)(Gg)(Gh)(Gi)(Gj)(Gk)(Gl)(Gm)(Gn)(Go)(Gp)(Gq)(Gr)(Gs)(Gt)(Gu)(Gv)(Gw)(Gx)(Gy)(Gz)
	(Ha)(Hb)(Hc)(Hd)(He)(Hf)(Hg)(Hh)(Hi)(Hj)(Hk)(Hl)(Hm)(Hn)(Ho)(Hp)(Hq)(Hr)(Hs)(Ht)(Hu)(Hv)(Hw)(Hx)(Hy)(Hz)
	(Ia)(Ib)(Ic)(Id)(Ie)(If)(Ig)(Ih)(Ii)(Ij)(Ik)(Il)(Im)(In)(Io)(Ip)(Iq)(Ir)(Is)(It)(Iu)(Iv)(Iw)(Ix)(Iy)(Iz)
	(Ja)(Jb)(Jc)(Jd)(Je)(Jf)(Jg)(Jh)(Ji)(Jj)(Jk)(Jl)(Jm)(Jn)(Jo)(Jp)(Jq)(Jr)(Js)(Jt)(Ju)(Jv)(Jw)(Jx)(Jy)(Jz)
	(Ka)(Kb)(Kc)(Kd)(Ke)(Kf)(Kg)(Kh)(Ki)(Kj)(Kk)(Kl)(Km)(Kn)(Ko)(Kp)(Kq)(Kr)(Ks)(Kt)(Ku)(Kv)(Kw)(Kx)(Ky)(Kz)
	(La)(Lb)(Lc)(Ld)(Le)(Lf)(Lg)(Lh)(Li)(Lj)(Lk)(Ll)(Lm)(Ln)(Lo)(Lp)(Lq)(Lr)(Ls)(Lt)(Lu)(Lv)(Lw)(Lx)(Ly)(Lz)
	(Ma)(Mb)(Mc)(Md)(Me)(Mf)(Mg)(Mh)(Mi)(Mj)(Mk)(Ml)(Mm)(Mn)(Mo)(Mp)(Mq)(Mr)(Ms)(Mt)(Mu)(Mv)(Mw)(Mx)(My)(Mz)
	(Na)(Nb)(Nc)(Nd)(Ne)(Nf)(Ng)(Nh)(Ni)(Nj)(Nk)(Nl)(Nm)(Nn)(No)(Np)(Nq)(Nr)(Ns)(Nt)(Nu)(Nv)(Nw)(Nx)(Ny)(Nz)
);

void test_all()
{
	leg_scoped ls = leg_scoped::ten;

	ben_scoped bs = ben_scoped::ten;

	unsigned long long ull = 4000;


	std::string lsstr;
	std::string bsstr;

	//lsstr = std::to_string(ls); //not allowed
	lsstr = std::to_string((int)ls);

	//bsstr = std::to_string(bs); //not allowed yet, maybe shouldn't be. Would be hard to implement.
	bsstr = std::to_string((int)bs);

	//----------
	//TODO: Automate

	std::cin >> reinterpret_cast<int&>(ls);

	std::cin >> bs;

	//-----------
	//TODO: Write to stringstream

	std::cout << /*ls<<*/ '\n'; //not allowed
	std::cout << (int)ls << '\n';

	std::cout << bs << '\n';
	std::cout << (int)bs << '\n';

	//----------

	int lsint;
	int bsint;

	//lsint = ls; //not allowed
	lsint = (int)ls;
	lsint = static_cast<int>(ls);

	//bsint = bs; //not allowed
	bsint = (int)bs;
	bsint = static_cast<int>(bs);


	ls = (leg_scoped)lsint;
	ls = static_cast<leg_scoped>(lsint);
	//ls = (leg_scoped)0.1234f;
	ls = (leg_scoped)ull;
	//ls = (leg_scoped)lu;

	bs = (ben_scoped)bsint;
	bs = static_cast<ben_scoped>(bsint);
	//bs = (ben_scoped)0.1234f;
	//bs = (ben_scoped)ull;		//throws exception
	//bs = (ben_scoped)ls;

	//----------



	Many::has_value((Many::UnderlyingT)Many::Nz);
	Many::has_value(((Many::UnderlyingT)Many::Nz) + 1);
}