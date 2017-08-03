#pragma once

#ifdef DSCAPTURE_EXPORTS
#define DSCAPTURE_API __declspec(dllexport)
#else
#define DSCAPTURE_API __declspec(dllimport)
#endif

#ifndef XTRA
#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif
#endif