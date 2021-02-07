#pragma once

#include <cstddef>
#include <atomic>

namespace detail
{
    typedef uint32_t GTypeId;

    template <typename TBase>
    class GClassTypeId
    {
    public:

        template <typename T>
        static GTypeId GetTypeId()
        {
            static const GTypeId id = m_nextTypeId++;
            return id;
        }

    private:

        static std::atomic<GTypeId> m_nextTypeId;
    };

    template <typename TBase>
    std::atomic<GTypeId> GClassTypeId<TBase>::m_nextTypeId(0);
}
