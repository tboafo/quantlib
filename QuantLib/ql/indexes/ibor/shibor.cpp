/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Cheng Li, DataYes

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file libor.cpp
    \brief base class for China Shibor indexes
*/

#include <ql/indexes/ibor/shibor.h>
#include <ql/currencies/asia.hpp>
#include <ql/time/calendars/china.hpp>
#include <ql/time/daycounters/actual360.hpp>

namespace QuantLib {

	namespace {

		BusinessDayConvention shiborConvention(const Period& p) {
			switch (p.units()) {
			case Days:
			case Weeks:
				return Following;
			case Months:
			case Years:
				return ModifiedFollowing;
			default:
				QL_FAIL("invalid time units");
			}
		}

	}

		Shibor::Shibor(
			const Period& tenor,
			const Handle<YieldTermStructure>& h) 
			: IborIndex("shibor", tenor, (tenor.units()==Days && tenor.length()==1)? 0:1, CNYCurrency(),
			China(China::IB),
			shiborConvention(tenor), false,
			Actual360(), h) {

		}

}