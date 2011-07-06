/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: XmlQuery2.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef XMLQuery2_H
#define XMLQuery2_H

#include <iostream>
#include <string>
#include <vector>
#include <libxml/tree.h>

namespace OpenSOAP {

  //DOM���
  class XmlQuery2 {

  public:
    typedef struct NameSpaceDefTag {
      std::string href;
      std::string prefix;
    } NameSpaceDef;

  public:
    XmlQuery2(const std::string& query);
    virtual ~XmlQuery2();
    
    //�l�̎擾
    //�擾�ł����true��Ԃ�
    //��RootQuery �� RootNode��n��
    //int getValue(xmlDocPtr& doc, xmlNodePtr node);
    int getValue(xmlDocPtr& doc, xmlNodePtr node, 
		 std::vector<std::string>& values);

    int attach(xmlDocPtr& doc, 
	       xmlNodePtr node,
	       xmlNodePtr parent,
	       const std::string& value,
	       bool updateFlg,
	       bool useNs,
	       const NameSpaceDef* nsDef,
	       int insPos = -1); //-1=prev, 1=next

    int del(xmlDocPtr& doc, 
	    xmlNodePtr node);
    //xmlNodePtr parent,
    //const std::string& value);

    void spy() const;

  protected:

    class DataSet {
    public:
      DataSet() : value(NULL) {}
      DataSet(const DataSet& ds) : value(NULL) {
	setName(ds.name);
	if (ds.value) { setValue(*(ds.value)); }
      } 

      ~DataSet() { if (value) { delete value; } }

      // get method
      const std::string& getName() const { return name; }
      //const std::string* getValue() const { return value; }
      const std::string getValue() const { return isNullValue() ? "" : *value; }

      // set method
      void setName(const std::string& aName) { name = aName; }
      //�l�̐ݒ�(�����l�Ƃ���)
      //���ŏI�I�Ȏ擾�ړI�l��XmlQuery2::value�̗v�f�Ƃ���
      //  �ݒ肳���
      void setValue(const std::string& aValue) { 
	if (!value) { 
	  value = new std::string(aValue); 
	}
	else {
	  *value = aValue;
	}
      }
      //�l�̏�����
      void clearValue() {
	if (value) {
	  delete value;
	  value = NULL;
	}
      }
      //�l��NULL���ǂ����B
      //NULL�łȂ���Ώ����l�BNULL�Ȃ�擾�������ړI�l�Ƃ��ď�������B
      bool isNullValue() const { return NULL == value ? true : false; }

      void spy() const {
          std::cerr << " name=[" << name << "]" << std::endl;
          std::cerr << " value=[" 
                    << (NULL == value ? "<null>" : *value) << "]" << std::endl;
      }

    protected:
      std::string name;
      std::string* value; //NULL�łȂ���Ώ����l�BNULL�Ȃ�擾�ړI�l
    };

    //�q�C���X�^���X�|�C���^
    XmlQuery2* next_;

    //std::string nodeName_; //����(�K�{)
    DataSet node_;

    //���̃m�[�h�̗v�f�l���ړI���ǂ����B
    //�v�f���͕K�{�ł��邽�߁A�v�f���L�肩�l�����ݒ�(NULL)�Ƃ���
    //�����ł͖ړI�l���ǂ������f�ł��Ȃ����߁B
    bool isTarget_; 

    //�����̒l��v�����Ă��邩�ǂ����B(??�������A?�͂P�̂�)
    //���Ă��Ȃ��ꍇ�͏��߂Ɍ����������ʂ��Ԃ����B
    bool isMulti_;

    //����
    std::vector<DataSet> attributes_;

    void addName(const std::string& nameToken);
    void addAttributes(const std::string& attrToken);

  };

} // end of namespace OpenSOAP


#endif /* XMLQuery2_H */
