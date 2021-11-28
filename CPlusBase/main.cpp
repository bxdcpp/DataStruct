#include "smart_ptr.h"
#include "test_virtual_class.h"
#include "test_operator_overload.h"
#include "test_stl.h"
#include "rvo.h"
#include "hjj_c11.h"

int main()
{
	//test_smartPtr();
	//bxd013::test_inherit();
	//bxd014::test_inherit();
	//bxd014::test_inherit2();
	//bxd015::test_Complex();
	//bxd016::test_complex();
	//bxd012::test_size();
	//stl001::test_use_array();
	//test_memory_layout(3);

	/*double a = 0;

	double b = 0;

	double c = 0;

	printf("&a=0x%X, &b=0x%X, &c=0x%X", &a, &b, &c);
	getchar();*/

	test_unnamed();
	test_named();
	test_duang();
	hjj_c11_test();
	return 0;

}