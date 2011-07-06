/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: XmlQuery.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef XMLQuery_H
#define XMLQuery_H

#include <iostream>
#include <string>
#include <vector>
#include <libxml/tree.h>

#include <OpenSOAP/Defines.h>

namespace OpenSOAP {

    //analyze DOM
    class OPENSOAP_CLASS XmlQuery {
    public:
        XmlQuery(const std::string& query);
        ~XmlQuery();
    
        //�l�̎擾
        //�擾�ł����true��Ԃ�
        //��RootQuery �� RootNode��n��
        //int getValue(xmlDocPtr& doc, xmlNodePtr node);
        int getValue(xmlDocPtr& doc, xmlNodePtr node, 
                     std::vector<std::string>& values);

        //�l�̊i�[�ꏊ
        //����������ꍇ�L��
        //can't use object in Win32 DLL interface, so declare as pointer.
        //std::vector<std::string> value;
        //std::vector<std::string>* values_;

        bool isMulti() const;
        
        void spy() const;
        
    protected:
        
        class OPENSOAP_CLASS DataSet {
        public:
            DataSet() : value_(NULL) {}
            DataSet(const DataSet& ds) : value_(NULL) {
                setName(ds.name);
                if (ds.value_) { setValue(*(ds.value_)); }
            } 
            
            ~DataSet() { if (value_) { delete value_; } }
            
            // get method
            const std::string& getName() const { return name; }
            //const std::string* getValue() const { return value; }
            const std::string getValue() const { 
                return isNullValue() ? "" : *value_; }
            
            // set method
            void setName(const std::string& aName) { name = aName; }
            //�l�̐ݒ�(�����l�Ƃ���)
            //���ŏI�I�Ȏ擾�ړI�l��XmlQuery::value�̗v�f�Ƃ���
            //  �ݒ肳���
            void setValue(const std::string& aValue);

            //�l�̏�����
            void clearValue() {
                if (value_) {
                    delete value_;
                    value_ = NULL;
                }
            }
            //�l��NULL���ǂ����B
            //NULL�łȂ���Ώ����l�BNULL�Ȃ�擾�������ړI�l�Ƃ��ď�������B
            bool isNullValue() const { return NULL == value_ ? true : false; }
            
            void spy() const {
                std::cerr << " name=[" << name << "]" << std::endl;
                std::cerr << " value_=[" 
                          << (NULL == value_ ? "<null>" : *value_) 
                          << "]" << std::endl;
            }

        protected:
            std::string name;
            std::string* value_; //NULL�łȂ���Ώ����l�BNULL�Ȃ�擾�ړI�l
        };
        
        //�q�C���X�^���X�|�C���^
        XmlQuery* next_;
        
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
        //can't use object in Win32 DLL interface, so declare as pointer.
        //std::vector<DataSet> attributes_;
        std::vector<DataSet>* attributes_;
        
        void addName(const std::string& nameToken);
        void addAttributes(const std::string& attrToken);
        
        std::string::size_type findDelmitPos(const std::string& s,
                                             std::string::size_type beginPos,
                                             const std::string del);
    };

} // end of namespace OpenSOAP


#endif /* XMLQuery_H */
