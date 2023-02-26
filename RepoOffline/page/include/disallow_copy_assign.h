#ifndef __SE_DISALLOW_COPY_ASSIGN_H__
#define __SE_DISALLOW_COPY_ASSIGN_H__

namespace search_engine{

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&);         \
        TypeName& operator=(const TypeName&)

} // namespace search_engine

#endif // __SE_DISALLOW_COPY_ASSIGN_H__
