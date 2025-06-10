#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <cmath>

namespace Framework
{
    using OffsetList = std::vector<uint32_t>;

    struct PatternByte {
        BYTE value;
        bool isWildcard;
    };

    struct AddressOffset {
        std::string name;
        std::string basePattern;
        OffsetList offsets;
    };

    struct Vector3 {
        float x;
        float y;
        float z;

        float Magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3 Normalized() const {
            float mag = Magnitude();
            if (mag > 0) {
                return { x / mag, y / mag, z / mag };
            }
            return { 0, 0, 0 };
        }

        Vector3 operator+(const Vector3& other) const {
            return { x + other.x, y + other.y, z + other.z };
        }

        Vector3 operator-(const Vector3& other) const {
            return { x - other.x, y - other.y, z - other.z };
        }
    };
}
