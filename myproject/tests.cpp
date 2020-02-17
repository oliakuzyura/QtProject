#include <vector>



TEST(MyVector, ConstructorFromArray_initialisedVectorWithCopyOfElementsFromArray)
{
    const int myArray[] = {4, 3, 5, 6};
    Vector<int> v(myArray);
}

TEST(MyVector, ConstructorFromStdVector_initialisedVectorWithCopyOfElementsFromSTDVector)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    Vector<int> v(v1);
}

TEST(MyVector, AccessByIndex)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    Vector<int> v(v1);

    for(size_t i=0; i<v1.size(); ++i){
        EXPECT_EQ(v1[i],v.at(i));
    }
}

TEST(MyVector, CopyConstructor)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    const Vector<int> v(v1);
    Vector<int> v2(v);
    for(size_t i=0; i<v.size(); ++i){
        EXPECT_EQ(v.at(i),v2.at(i));
    }
}
TEST(MyVector, MoveConstructor)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    Vector<int> v(v1);
    Vector<int> v2(std::move(v));
    EXPECT_EQ(v1.size(),v2.size());
    EXPECT_EQ(0, v.size());
    for(size_t i=0; i<v.size(); ++i)
    {
        EXPECT_EQ(v2.at(i),v1[i]);
    }
}

TEST(MyVector, CheckSize)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    Vector<int> v(v1);

    EXPECT_EQ(v1.size(),v.size());
}

struct IsOdd
{
    bool operator()(int number)
    {
        return number % 2 == 1;
    }
};

TEST(MyVector, ConditionalCounting)
{
    const std::vector<int> v1 = {4, 3, 5, 6};
    Vector<int> v(v1);

    EXPECT_EQ(count_if(begin(v1), end(v1), IsOdd()),
              v.count_if(IsOdd()));
}
