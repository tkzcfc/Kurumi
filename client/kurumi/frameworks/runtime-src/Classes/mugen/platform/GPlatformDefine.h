#pragma once

#define NS_G_BEGIN namespace ng {
#define NS_G_END }
#define USING_NS_G using namespace ng
#define NS_G ::ng

#define G_ASSERT assert

#define G_DEBUG _DEBUG

// G_FORCEINLINE
#if defined(AE_VCPP) || defined(AE_ICC)
#define G_FORCEINLINE __forceinline
#elif defined(AE_GCC)
//#define G_FORCEINLINE __attribute__((always_inline)) 
#define G_FORCEINLINE inline
#else
#define G_FORCEINLINE inline
#endif

#define G_SYNTHESIZE_HEADER G_FORCEINLINE
//#define G_SYNTHESIZE_HEADER virtual G_FORCEINLINE

#define G_SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType& get##funName(void) { return varName; }

#define G_SYNTHESIZE_REF_PTR(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType* get##funName(void) { return &varName; }


#define G_SYNTHESIZE(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType get##funName(void) const { return varName; } G_SYNTHESIZE_HEADER void set##funName(varType var){ varName = var; }

#define G_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType get##funName(void) const { return varName; }

#define G_SYNTHESIZE_WRITEONLY(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER void set##funName(varType var){ varName = var; }


#define G_SYNTHESIZE_IS(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType is##funName(void) const { return varName; } G_SYNTHESIZE_HEADER void set##funName(varType var){ varName = var; }

#define G_SYNTHESIZE_IS_READONLY(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER varType is##funName(void) const { return varName; }



#define G_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER const varType& get##funName(void) const { return varName; } G_SYNTHESIZE_HEADER void set##funName(const varType& var){ varName = var; }

#define G_SYNTHESIZE_READONLY_BY_REF(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER const varType& get##funName(void) const { return varName; }

#define G_SYNTHESIZE_WRITEONLY_BY_REF(varType, varName, funName)\
protected: varType varName; public: G_SYNTHESIZE_HEADER void set##funName(const varType& var){ varName = var; }



#define G_PROPERTY(varType, varName, funName)\
protected: varType varName; public: virtual varType get##funName(void) const; virtual void set##funName(varType var);

#define G_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName; public: virtual varType get##funName(void) const;

#define G_PROPERTY_WRITEONLY(varType, varName, funName)\
protected: varType varName; public: virtual void set##funName(varType var);



#define G_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName; public: virtual const varType& get##funName(void) const; virtual void set##funName(const varType& var);

#define G_PROPERTY_READONLY_BY_REF(varType, varName, funName)\
protected: varType varName; public: virtual const varType& get##funName(void) const;

#define G_PROPERTY_WRITEONLY_BY_REF(varType, varName, funName)\
protected: varType varName; public: virtual void set##funName(const varType& var);

#define G_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define G_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define G_BREAK_IF(cond)           if(cond) break


#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX



//! 位操作相关
#define G_BIT_SET(b, flag) (b) |= (flag)
#define G_BIT_GET(b, flag) ((b) & (flag))
#define G_BIT_REMOVE(b, flag) (b) &= ~(flag)
#define G_BIT_EQUAL(b, flag) ((b) & (flag)) == (flag)
#define G_BIT_NO_EQUAL(b, flag) ((b) & (flag)) != (flag)


#define G_GetComponent(entity, component) dynamic_cast<component*>((entity)->getComponent(#component))
