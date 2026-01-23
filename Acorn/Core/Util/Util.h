#pragma once

#include <memory>
#include <utility>
#include <functional>

namespace Acorn {

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ...Args>
    std::shared_ptr<T> MakeRef(Args&&... args) 
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ...Args>
    std::unique_ptr<T> MakeRef(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Function = std::function<T()>;
}