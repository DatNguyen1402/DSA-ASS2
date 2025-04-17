#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D;

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list);

template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    void removeAt(int index){
        pList->removeAt(index);
    }
    string toString() const;

    friend ostream &operator<< <T>(ostream &os, const List1D<T> &list);
};

// -------------------- List2D --------------------
template <typename T>
class List2D;

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &list);
template <typename T>
class List2D
{
    private:
    IList<List1D<T> *> *pMatrix;
    
    public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();
    
    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    void addRow(const List1D<T>& row);
    void removeAt(int rowIndex);
    
    List1D<T> getRow(int rowIndex) const;
    string toString() const;
    
     
    friend ostream &operator<< <T>(ostream &os, const List2D<T> &matrix);
};

bool compareDouble(double a, double b){
    double diff = (a-b < 0) ? b-a : a-b;
    return diff < 1e-8;
}
struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
    InventoryAttribute() : name(""), value(0.0) {}
    double getValue() const {return value;}
    bool operator==(const InventoryAttribute &other) const {
        return name == other.name && compareDouble(value, other.value);
    }
    
    friend ostream& operator<<(ostream& os, const InventoryAttribute& attr) {
        return os << attr.toString();
    }
    
};


// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;


    public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
    
    // helper function

    double getAttrValue(string name, const List1D<InventoryAttribute> row) const;

    
    void sort(List1D<int>& list, string name ,bool ascending) const;
    bool isSameAttribute(const List1D<InventoryAttribute>& row1, const List1D<InventoryAttribute>& row2) const;

};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new XArrayList<T>();

}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    // TODO
    pList = new XArrayList<T>();

    for (int i = 0; i < num_elements; i++){
        pList->add(T()); // initialize with default value = 0
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++){
        pList->add(array[i]); 
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    pList = new XArrayList<T>();

    for (int i = 0; i < other.pList->size(); i++) {
        pList->add(other.pList->get(i));
    }

}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    // delete pList;
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
    T& target = pList->get(index);
    target = value;
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    return pList->toString();
}

template <typename T>
ostream &  operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString();
    return os;
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    pMatrix = new DLinkedList<List1D<T>*>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    // TODO
    pMatrix = new DLinkedList<List1D<T>*>();
    for (int i = 0; i< num_rows; i++){        
        pMatrix->add(new List1D<T>(array[i]));
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    // TODO
    pMatrix = new DLinkedList<List1D<T>*>();
    for (int i = 0; i< other.pMatrix->size(); i++){
        pMatrix->add(new List1D<T>(*other.pMatrix->get(i)));
        
    }
}


template <typename T>
List2D<T>::~List2D()
{
    // TODO
    // for (int i = 0; i < pMatrix->size(); i++) {
    //     delete pMatrix->get(i);  
    // }
    // delete pMatrix;  
}

template <typename T>
int List2D<T>::rows() const
{
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    List1D<T>*& target = pMatrix->get(rowIndex);
    delete target;
    target = new List1D<T>(row);
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    // TODO
    return pMatrix->get(rowIndex)->get(colIndex);
}


template <typename T>
void List2D<T>::addRow(const List1D<T>& row)
{
    // TODO
    pMatrix->add(new List1D<T>(row));
}

template <typename T>
void List2D<T>::removeAt(int rowIndex){
    pMatrix->removeAt(rowIndex);
}


template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    // TODO
    List1D<T>* row = pMatrix->get(rowIndex);
    return *row;
}

template <typename T>
string List2D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";

    for (int i = 0; i < pMatrix->size(); i++) {
        if (i > 0) ss << ", ";
        ss << pMatrix->get(i)->toString();  
    }

    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString();
    return os;
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO
    this->attributesMatrix = matrix;
    this->productNames = names;
    this->quantities = quantities;
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
    this->attributesMatrix = other.attributesMatrix;
    this->productNames = other.productNames;
    this->quantities = other.quantities;
}

int InventoryManager::size() const
{
    // TODO
    // int sum = 0;
    // for (int i = 0; i < quantities.size(); i++){
    //     sum += quantities.get(i);
    // }
    // return sum;
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    attributesMatrix.addRow(attributes);
    productNames.add(name);
    quantities.add(quantity);
    
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    attributesMatrix.removeAt(index);
    productNames.removeAt(index);
    quantities.removeAt(index);
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<int> result = List1D<int>();

    for (int i = 0; i < size(); i++){
        if (quantities.get(i) < minQuantity) continue;
        List1D<InventoryAttribute> row = attributesMatrix.getRow(i);
        for (int j = 0; j < row.size(); j++){
            double value = getAttrValue(attributeName, row);
            if (value == -1) continue;
            if (value >= minValue && value <= maxValue){
                result.add(i);  //add index to result
                break; 
            }
        }
    }
    //sort
    sort(result, attributeName, ascending);

    // result
    List1D<string> resultName = List1D<string>();

    for (int i = 0; i < result.size(); i++){
        resultName.add(productNames.get(result.get(i)));
    }
    
    return resultName;
}



void InventoryManager::sort(List1D<int>& list, string name ,bool ascending) const {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double leftVal = getAttrValue(name, attributesMatrix.getRow(list.get(j)));
            double rightVal = getAttrValue(name, attributesMatrix.getRow(list.get(j+1)));
            //test
            // cout << leftVal << " " << rightVal << "- sort?" << endl;

            bool isEqualVal = compareDouble(leftVal, rightVal);
            bool isSwap = false;

            int index1 = list.get(j);
            int index2 = list.get(j+1);

            if (isEqualVal){
                int quantity1 = getProductQuantity(index1);
                int quantity2 = getProductQuantity(index2);
                isSwap = (ascending && quantity1 >  quantity2 )|| (!ascending && quantity1 < quantity2) || (!ascending && quantity1 == quantity2);
            }
            else {
                isSwap = (ascending && leftVal > rightVal) || (!ascending && leftVal < rightVal);
            }



            if (isSwap){
                list.set(j, index2);
                list.set(j+1, index1);      
            }
        }
    }
}


double InventoryManager::getAttrValue(string name, const List1D<InventoryAttribute> row) const{
    for (int i = 0; i < row.size(); i++){
        InventoryAttribute attributeEle = row.get(i);
        if (attributeEle.name == name) return attributeEle.value;
    }
    return -1;
}


void InventoryManager::removeDuplicates()
{
    // TODO

    for (int i = 0; i < size(); i++) {
        for (int j = i + 1; j < size(); ) {
            if (productNames.get(i) == productNames.get(j) && isSameAttribute(attributesMatrix.getRow(i), attributesMatrix.getRow(j))) {
                quantities.set(i, quantities.get(i) + quantities.get(j));

                productNames.removeAt(j);
                quantities.removeAt(j);
                attributesMatrix.removeAt(j);  

            } else {
                j++;
            }
        }
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO

    InventoryManager newInven(inv1);

    for (int i = 0; i < inv2.size(); i++) {
        newInven.addProduct(inv2.getProductAttributes(i),inv2.getProductName(i),inv2.getProductQuantity(i));    
    }
    
    // newInven.removeDuplicates();

    return newInven;
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    double raw = size() * ratio;
    int splitIndex = (raw == (int)raw) ? (int)raw : (int)raw + 1;


    for (int i = 0; i < size(); i++) {
        string name = productNames.get(i);
        int quantity = quantities.get(i);
        List1D<InventoryAttribute> attributes = attributesMatrix.getRow(i);

        if (i < splitIndex){
            section1.productNames.add(name);
            section1.attributesMatrix.addRow(attributes); 
            section1.quantities.add(quantity);
        }
        else{
            section2.productNames.add(name);
            section2.attributesMatrix.addRow(attributes);
            section2.quantities.add(quantity);
        }
    }
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return quantities;
}

bool InventoryManager::isSameAttribute(const List1D<InventoryAttribute>& row1, const List1D<InventoryAttribute>& row2) const {
    if (row1.size() != row2.size()) return false;
    for (int i = 0; i < row1.size(); i++) {
        InventoryAttribute a = row1.get(i);
        InventoryAttribute b = row2.get(i);
        if (!(a==b)) {
            return false;
        }
    }
    return true;
}

string InventoryManager::toString() const
{
    // TODO
    stringstream ss;
    ss << "InventoryManager[\n";
    ss << "  AttributesMatrix: " ;
    ss << attributesMatrix.toString() ;
    ss << ",\n";
    ss << "  ProductNames: ";
    ss << productNames.toString();
    ss << ",\n";
    ss << "  Quantities: ";
    ss << quantities.toString();
    ss << "\n";
    ss << "]";
    return ss.str();
}

#endif /* INVENTORY_MANAGER_H */
