#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <memory>
#include <optional>
#include <vector>
#include "Color.hpp"
#include "Vector3D.hpp"
#include "IObject.hpp"

template <typename CoordType>
class Scene {
 public:
  Color Trace(math::Ray<CoordType> ray) {
    std::optional<CoordType> min_distance{std::nullopt};
    objects::IObjectPtr<CoordType> closest_object{nullptr};

    for (const auto& object : objects_) {
      auto intersection = object->Intersects(ray);
      if (intersection.has_value()) {
        if (!min_distance.has_value() ||
            min_distance.value() > intersection.value()) {
          min_distance = intersection.value();
          closest_object = object;
        }
      }
    }

    if (min_distance.has_value()) {
      return closest_object->IntersectColor(ray);
    } else {
      return Color::Default();
    }
  }

  void AddObject(objects::IObjectPtr<CoordType> object) {
    objects_.push_back(std::move(object));
  }

 private:
  std::vector<objects::IObjectPtr<CoordType>> objects_;
};

#endif RAYTRACER_SCENE_HPP
