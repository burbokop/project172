#include "sharedcontainer.h"

namespace e172 {


SharedContainer::ptr SharedContainer::id() const { return m_id; }

SharedContainer::data_ptr SharedContainer::data() const {
    return m_data;
}

void SharedContainer::setData(const data_ptr &data) {
    m_data = data;
}


SharedContainer::SharedContainer() {}

void SharedContainer::__detach() {
    if(ref_count_ptr) {
        --(*ref_count_ptr);
        if(*ref_count_ptr <= 0) {
            if(!m_destructor && m_data) {
                throw std::runtime_error("[e172::SharedContainer]: destructor is not set\n");
            }

            m_destructor(m_data);
            delete ref_count_ptr;
        }
    } else if(m_data) {
        throw std::runtime_error("[e172::SharedContainer]: detaching broken object\n");
    }
}

SharedContainer::SharedContainer(const SharedContainer &obj) {
    operator=(obj);
}

void SharedContainer::operator=(const SharedContainer &obj) {
    __detach();

    m_destructor = obj.m_destructor;
    m_data = obj.m_data;
    ref_count_ptr = obj.ref_count_ptr;
    m_id = obj.m_id;

    if(ref_count_ptr)
        ++(*ref_count_ptr);
}

SharedContainer::~SharedContainer() {
    __detach();
}

bool SharedContainer::isValid() const {
    return m_data != nullptr;
}

bool SharedContainer::isNull() const {
    return m_data == nullptr;
}

SharedContainer::base_handle::~base_handle() {}


}
