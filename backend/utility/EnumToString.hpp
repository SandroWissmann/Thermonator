#ifndef THERMONATOR_UTILITY_ENUMTOSTRING_HPP
#define THERMONATOR_UTILITY_ENUMTOSTRING_HPP

#include <QString>
#include <QVariant>

namespace thermonator::utility {

template <typename QEnum> QString enumToString(const QEnum value)
{
    auto variant = QVariant::fromValue(value);
    return variant.toString();
}

} // namespace thermonator::utility

#endif
