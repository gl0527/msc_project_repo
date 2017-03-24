#pragma once

#define GameObject_sptr std::shared_ptr<GameObject>
#define GameObject_wptr std::weak_ptr<GameObject>
#define GameObject_uptr std::unique_ptr<GameObject>
#define Component_sptr std::shared_ptr<Component>
#define Component_wptr std::weak_ptr<Component>

#define MYNAMESPACE_EXPORT

#ifdef MYNAMESPACE_EXPORT
#define DLL_SPEC __declspec(dllexport)
#else
#define DLL_SPEC __declspec(dllimport)
#endif