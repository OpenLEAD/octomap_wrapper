#include <boost/test/unit_test.hpp>
#include <octomap_wrapper/Dummy.hpp>

using namespace octomap_wrapper;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    octomap_wrapper::DummyClass dummy;
    dummy.welcome();
}
