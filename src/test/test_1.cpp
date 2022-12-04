#include "pch.hpp"
#include "utils.hpp"
#include "catch.hpp"

TEST_CASE("Test LOG 1", "[all][basic]")
{

	SECTION("Section print 1")
	{

		LOG(LogLvl::DEBUG) << "TEST0";
		LOG(LogLvl::INFO) << "TEST1";
		LOG(LogLvl::WARN) << "TEST2";
		LOG(LogLvl::ERROR) << "TEST3";

		REQUIRE(Log::ReportingLevel() == LogLvl::DEBUG);
		REQUIRE(static_cast<LogLvl>(2) == LogLvl::WARN);
		REQUIRE(Log::toString(static_cast<LogLvl>(3)) == "ERROR");
	}

	SECTION("Section print 2")
	{
		LOG::ReportingLevel() = LogLvl::WARN;
		LOG(LogLvl::DEBUG) << "TEST0";
		LOG(LogLvl::INFO) << "TEST1";
		LOG(LogLvl::WARN) << "TEST2";
		LOG(LogLvl::ERROR) << "TEST3";
		LOG::ReportingLevel() = LogLvl::DEBUG;
	}
}

TEST_CASE("Test split_string 1", "[all][basic]")
{

	SECTION("Section split parts 1")
	{
		auto parts = split_string("n,5,,,", ",");
		REQUIRE(parts.size() == 5);
	}

	SECTION("Section split parts 2")
	{
		std::string s(" 12 – 40;  may send 12, 41, 42, 43, 44, 45, 46, 47  ");
		remove_spaces(s);
		auto parts = split_string(s, "=");
		REQUIRE(parts.size() == 1);
	}

	SECTION("Section split parts 3")
	{
		std::string s("");
		auto parts = split_string(s, "=");
		REQUIRE(parts.size() == 1);
	}

	SECTION("Section split parts 4")
	{
		std::string s("");
		replace_all(s, ">", "=");
		REQUIRE(s.empty() == true);
	}

	SECTION("Section split parts 5")
	{
		std::string s(">>>>>>");
		replace_all(s, ">", "");
		REQUIRE(s.empty() == true);
	}

	SECTION("Section split parts 6")
	{
		std::string s("some");
		replace_all(s, "", "=");
		REQUIRE(s.empty() == false);
	}
}
