#include <ATen/core/Dict.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using std::string;
using c10::Dict;

TEST(DictTest, givenEmptyDict_whenCallingEmpty_thenReturnsTrue) {
    Dict<int64_t, string> dict;
    EXPECT_TRUE(dict.empty());
}

TEST(DictTest, givenNonemptyDict_whenCallingEmpty_thenReturnsFalse) {
    Dict<int64_t, string> dict;
    dict.insert(3, "value");
    EXPECT_FALSE(dict.empty());
}

TEST(DictTest, givenEmptyDict_whenCallingSize_thenReturnsZero) {
    Dict<int64_t, string> dict;
    EXPECT_EQ(0, dict.size());
}

TEST(DictTest, givenNonemptyDict_whenCallingSize_thenReturnsNumberOfElements) {
    Dict<int64_t, string> dict;
    dict.insert(3, "value");
    dict.insert(4, "value2");
    EXPECT_EQ(2, dict.size());
}

TEST(DictTest, givenNonemptyDict_whenCallingClear_thenIsEmpty) {
  Dict<int64_t, string> dict;
  dict.insert(3, "value");
  dict.insert(4, "value2");
  dict.clear();
  EXPECT_TRUE(dict.empty());
}

TEST(DictTest, whenInsertingNewKey_thenReturnsTrueAndIteratorToNewElement) {
  Dict<int64_t, string> dict;
  std::pair<Dict<int64_t, string>::iterator, bool> result = dict.insert(3, "value");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(3, result.first->key());
  EXPECT_EQ("value", result.first->value());
}

TEST(DictTest, whenInsertingExistingKey_thenReturnsFalseAndIteratorToExistingElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "old_value");
  std::pair<Dict<int64_t, string>::iterator, bool> result = dict.insert(3, "new_value");
  EXPECT_FALSE(result.second);
  EXPECT_EQ(3, result.first->key());
  EXPECT_EQ("old_value", result.first->value());
}

TEST(DictTest, whenInsertingExistingKey_thenDoesNotModifyDict) {
  Dict<int64_t, string> dict;
  dict.insert(3, "old_value");
  dict.insert(3, "new_value");
  EXPECT_EQ(1, dict.size());
  EXPECT_EQ(3, dict.begin()->key());
  EXPECT_EQ("old_value", dict.begin()->value());
}

TEST(DictTest, whenInsertOrAssigningNewKey_thenReturnsTrueAndIteratorToNewElement) {
  Dict<int64_t, string> dict;
  std::pair<Dict<int64_t, string>::iterator, bool> result = dict.insert_or_assign(3, "value");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(3, result.first->key());
  EXPECT_EQ("value", result.first->value());
}

TEST(DictTest, whenInsertOrAssigningExistingKey_thenReturnsFalseAndIteratorToChangedElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "old_value");
  std::pair<Dict<int64_t, string>::iterator, bool> result = dict.insert_or_assign(3, "new_value");
  EXPECT_FALSE(result.second);
  EXPECT_EQ(3, result.first->key());
  EXPECT_EQ("new_value", result.first->value());
}

TEST(DictTest, whenInsertOrAssigningExistingKey_thenDoesModifyDict) {
  Dict<int64_t, string> dict;
  dict.insert(3, "old_value");
  dict.insert_or_assign(3, "new_value");
  EXPECT_EQ(1, dict.size());
  EXPECT_EQ(3, dict.begin()->key());
  EXPECT_EQ("new_value", dict.begin()->value());
}

TEST(DictTest, givenEmptyDict_whenIterating_thenBeginIsEnd) {
  Dict<int64_t, string> dict;
  const Dict<int64_t, string> cdict;
  EXPECT_EQ(dict.begin(), dict.end());
  EXPECT_EQ(dict.cbegin(), dict.cend());
  EXPECT_EQ(cdict.begin(), cdict.end());
  EXPECT_EQ(cdict.cbegin(), cdict.cend());
}

TEST(DictTest, givenMutableDict_whenIterating_thenFindsElements) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(5, "5");
  bool found_first = false;
  bool found_second = false;
  for (Dict<int64_t, string>::iterator iter = dict.begin(); iter != dict.end(); ++iter) {
    if (iter->key() == 3) {
      EXPECT_EQ("3", iter->value());
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (iter->key() == 5) {
      EXPECT_EQ("5", iter->value());
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(DictTest, givenMutableDict_whenIteratingWithForeach_thenFindsElements) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(5, "5");
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : dict) {
    if (elem.key() == 3) {
      EXPECT_EQ("3", elem.value());
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem.key() == 5) {
      EXPECT_EQ("5", elem.value());
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(DictTest, givenConstDict_whenIterating_thenFindsElements) {
  Dict<int64_t, string> dict_;
  dict_.insert(3, "3");
  dict_.insert(5, "5");
  const Dict<int64_t, string>& dict = dict_;
  bool found_first = false;
  bool found_second = false;
  for (Dict<int64_t, string>::const_iterator iter = dict.begin(); iter != dict.end(); ++iter) {
    if (iter->key() == 3) {
      EXPECT_EQ("3", iter->value());
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (iter->key() == 5) {
      EXPECT_EQ("5", iter->value());
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(DictTest, givenConstDict_whenIteratingWithForeach_thenFindsElements) {
  Dict<int64_t, string> dict_;
  dict_.insert(3, "3");
  dict_.insert(5, "5");
  const Dict<int64_t, string>& dict = dict_;
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : dict) {
    if (elem.key() == 3) {
      EXPECT_EQ("3", elem.value());
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem.key() == 5) {
      EXPECT_EQ("5", elem.value());
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(DictTest, givenIterator_thenCanModifyValue) {
  Dict<int64_t, string> dict;
  dict.insert(3, "old_value");
  dict.begin()->setValue("new_value");
  EXPECT_EQ("new_value", dict.begin()->value());
}

TEST(DictTest, givenOneElementDict_whenErasingByConstIterator_thenDictIsEmpty) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.erase(dict.cbegin());
  EXPECT_TRUE(dict.empty());
}

TEST(DictTest, givenOneElementDict_whenErasingByIterator_thenDictIsEmpty) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.erase(dict.begin());
  EXPECT_TRUE(dict.empty());
}

TEST(DictTest, givenOneElementDict_whenErasingByKey_thenReturnsOneAndDictIsEmpty) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  bool result = dict.erase(3);
  EXPECT_EQ(1, result);
  EXPECT_TRUE(dict.empty());
}

TEST(DictTest, givenOneElementDict_whenErasingByNonexistingKey_thenReturnsZeroAndDictIsUnchanged) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  bool result = dict.erase(4);
  EXPECT_EQ(0, result);
  EXPECT_EQ(1, dict.size());
}

TEST(DictTest, whenCallingAtWithExistingKey_thenReturnsCorrectElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  EXPECT_EQ("4", dict.at(4));
}

TEST(DictTest, whenCallingAtWithNonExistingKey_thenReturnsCorrectElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  EXPECT_THROW(dict.at(5), std::out_of_range);
}

TEST(DictTest, givenMutableDict_whenCallingFindOnExistingKey_thenFindsCorrectElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  Dict<int64_t, string>::iterator found = dict.find(3);
  EXPECT_EQ(3, found->key());
  EXPECT_EQ("3", found->value());
}

TEST(DictTest, givenMutableDict_whenCallingFindOnNonExistingKey_thenReturnsEnd) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  Dict<int64_t, string>::iterator found = dict.find(5);
  EXPECT_EQ(dict.end(), found);
}

TEST(DictTest, givenConstDict_whenCallingFindOnExistingKey_thenFindsCorrectElement) {
  Dict<int64_t, string> dict_;
  dict_.insert(3, "3");
  dict_.insert(4, "4");
  const Dict<int64_t, string>& dict = dict_;
  Dict<int64_t, string>::const_iterator found = dict.find(3);
  EXPECT_EQ(3, found->key());
  EXPECT_EQ("3", found->value());
}

TEST(DictTest, givenConstDict_whenCallingFindOnNonExistingKey_thenReturnsEnd) {
  Dict<int64_t, string> dict_;
  dict_.insert(3, "3");
  dict_.insert(4, "4");
  const Dict<int64_t, string>& dict = dict_;
  Dict<int64_t, string>::const_iterator found = dict.find(5);
  EXPECT_EQ(dict.end(), found);
}

TEST(DictTest, whenCallingContainsWithExistingKey_thenReturnsTrue) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  EXPECT_TRUE(dict.contains(3));
}

TEST(DictTest, whenCallingContainsWithNonExistingKey_thenReturnsFalse) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");
  EXPECT_FALSE(dict.contains(5));
}

TEST(DictTest, whenCallingReserve_thenDoesntCrash) {
  Dict<int64_t, string> dict;
  dict.reserve(100);
}

TEST(DictTest, whenCopyConstructingDict_thenAreEqual) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2(dict1);

  EXPECT_EQ(2, dict2.size());
  EXPECT_EQ("3", dict2.at(3));
  EXPECT_EQ("4", dict2.at(4));
}

TEST(DictTest, whenCopyAssigningDict_thenAreEqual) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2;
  dict2 = dict1;

  EXPECT_EQ(2, dict2.size());
  EXPECT_EQ("3", dict2.at(3));
  EXPECT_EQ("4", dict2.at(4));
}

TEST(DictTest, whenCopyingDict_thenAreEqual) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2 = dict1.copy();

  EXPECT_EQ(2, dict2.size());
  EXPECT_EQ("3", dict2.at(3));
  EXPECT_EQ("4", dict2.at(4));
}

TEST(DictTest, whenMoveConstructingDict_thenNewIsCorrect) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2(std::move(dict1));

  EXPECT_EQ(2, dict2.size());
  EXPECT_EQ("3", dict2.at(3));
  EXPECT_EQ("4", dict2.at(4));
}

TEST(DictTest, whenMoveAssigningDict_thenNewIsCorrect) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2;
  dict2 = std::move(dict1);

  EXPECT_EQ(2, dict2.size());
  EXPECT_EQ("3", dict2.at(3));
  EXPECT_EQ("4", dict2.at(4));
}

TEST(DictTest, whenMoveConstructingDict_thenOldIsEmpty) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2(std::move(dict1));
  EXPECT_TRUE(dict1.empty());
}

TEST(DictTest, whenMoveAssigningDict_thenOldIsEmpty) {
  Dict<int64_t, string> dict1;
  dict1.insert(3, "3");
  dict1.insert(4, "4");

  Dict<int64_t, string> dict2;
  dict2 = std::move(dict1);
  EXPECT_TRUE(dict1.empty());
}

TEST(DictTest, givenMutableIterator_whenAssigningToConstIterator_thenWorks) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  Dict<int64_t, string>::iterator iter = dict.begin();
  Dict<int64_t, string>::const_iterator const_iter = iter;
  EXPECT_EQ(3, const_iter->key());
  EXPECT_EQ("3", const_iter->value());
}

TEST(DictTest, givenMutableIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::iterator iter1 = dict.begin();
  Dict<int64_t, string>::iterator iter2 = iter1++;
  EXPECT_NE(dict.begin()->key(), iter1->key());
  EXPECT_EQ(dict.begin()->key(), iter2->key());
}

TEST(DictTest, givenConstIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::const_iterator iter1 = dict.cbegin();
  Dict<int64_t, string>::const_iterator iter2 = iter1++;
  EXPECT_NE(dict.begin()->key(), iter1->key());
  EXPECT_EQ(dict.begin()->key(), iter2->key());
}

TEST(DictTest, givenMutableIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::iterator iter1 = dict.begin();
  Dict<int64_t, string>::iterator iter2 = ++iter1;
  EXPECT_NE(dict.begin()->key(), iter1->key());
  EXPECT_NE(dict.begin()->key(), iter2->key());
}

TEST(DictTest, givenConstIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::const_iterator iter1 = dict.cbegin();
  Dict<int64_t, string>::const_iterator iter2 = ++iter1;
  EXPECT_NE(dict.begin()->key(), iter1->key());
  EXPECT_NE(dict.begin()->key(), iter2->key());
}

TEST(DictTest, givenEqualMutableIterators_thenAreEqual) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::iterator iter1 = dict.begin();
  Dict<int64_t, string>::iterator iter2 = dict.begin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(DictTest, givenDifferentMutableIterators_thenAreNotEqual) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::iterator iter1 = dict.begin();
  Dict<int64_t, string>::iterator iter2 = dict.begin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(DictTest, givenEqualConstIterators_thenAreEqual) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::const_iterator iter1 = dict.cbegin();
  Dict<int64_t, string>::const_iterator iter2 = dict.cbegin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(DictTest, givenDifferentConstIterators_thenAreNotEqual) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");
  dict.insert(4, "4");

  Dict<int64_t, string>::const_iterator iter1 = dict.cbegin();
  Dict<int64_t, string>::const_iterator iter2 = dict.cbegin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(DictTest, givenMutableIterator_whenDereferencing_thenPoint64_tsToCorrectElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");

  Dict<int64_t, string>::iterator iter = dict.begin();
  EXPECT_EQ(3, (*iter).key());
  EXPECT_EQ("3", (*iter).value());
  EXPECT_EQ(3, iter->key());
  EXPECT_EQ("3", iter->value());
}

TEST(DictTest, givenConstIterator_whenDereferencing_thenPoint64_tsToCorrectElement) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");

  Dict<int64_t, string>::const_iterator iter = dict.cbegin();
  EXPECT_EQ(3, (*iter).key());
  EXPECT_EQ("3", (*iter).value());
  EXPECT_EQ(3, iter->key());
  EXPECT_EQ("3", iter->value());
}

TEST(DictTest, givenMutableIterator_whenWritingToValue_thenWorks) {
  Dict<int64_t, string> dict;
  dict.insert(3, "3");

  Dict<int64_t, string>::iterator iter = dict.begin();

  (*iter).setValue("new_value");
  EXPECT_EQ("new_value", dict.begin()->value());

  iter->setValue("new_value_2");
  EXPECT_EQ("new_value_2", dict.begin()->value());
}

TEST(DictTest, isReferenceType) {
  Dict<int64_t, string> dict1;
  Dict<int64_t, string> dict2(dict1);
  Dict<int64_t, string> dict3;
  dict3 = dict1;

  dict1.insert(3, "three");
  EXPECT_EQ(1, dict1.size());
  EXPECT_EQ(1, dict2.size());
  EXPECT_EQ(1, dict3.size());
}

TEST(DictTest, copyHasSeparateStorage) {
  Dict<int64_t, string> dict1;
  Dict<int64_t, string> dict2(dict1.copy());
  Dict<int64_t, string> dict3;
  dict3 = dict1.copy();

  dict1.insert(3, "three");
  EXPECT_EQ(1, dict1.size());
  EXPECT_EQ(0, dict2.size());
  EXPECT_EQ(0, dict3.size());
}
