#pragma once
#include <tuple>
#include <vector>
#include <map>

/// \brief Proxy class for matrix cell
template<typename T>
class MatrixCell
{
public:
	/// \brief Constructs matrix cell using row and column indexes
	MatrixCell(std::map<std::tuple<size_t, size_t>, T>& points, T& defaultValue, size_t rowIdx, size_t colIdx) 
		: m_points(points), m_defaultValue(defaultValue), m_rowIdx(rowIdx), m_colIdx(colIdx) {}

	/// \brief Assigns a value to the matrix cell
	/// \details If value equals to the default - clears cell
	MatrixCell& operator=(T value)
	{
		auto key = std::make_tuple(m_rowIdx, m_colIdx);
		if (value == m_defaultValue)
		{ // special case - clear cell value to optimize memory usage
			if (m_points.find(key) != m_points.end())
				m_points.erase(key);
		}
		else
			m_points[key] = value;
		return *this;
	}

// 	operator T& ()
// 	{
// 		auto key = std::make_tuple(m_rowIdx, m_colIdx);
// 		if (auto it = m_points.find(key); it == m_points.end())
// 			return m_defaultValue;
// 		return m_points[key];
// 	}

	/// \brief Implicit cast operator
	/// \details For comparisons like matrix[0][0] == value
	operator T& () const
	{
		auto key = std::make_tuple(m_rowIdx, m_colIdx);
		if (auto it = m_points.find(key); it == m_points.end())
			return m_defaultValue;
		return m_points[key];
	}

protected:
	std::map<std::tuple<size_t, size_t>, T>& m_points;
	T& m_defaultValue;
	size_t m_rowIdx;
	size_t m_colIdx;
};

/// \brief Proxy class for matrix row
template<typename T>
class MatrixRow
{
public:
	/// \brief Constructs matrix cell using row index
	MatrixRow(std::map<std::tuple<size_t, size_t>, T>& points, T &defaultValue, size_t rowIdx) : 
		m_points(points), m_defaultValue(defaultValue), m_rowIdx(rowIdx) {}

	MatrixCell<T> operator[](size_t idx)
	{
		MatrixCell<T> res{ m_points, m_defaultValue, m_rowIdx, idx };
		return res;
	}

protected:
	T& m_defaultValue;
	std::map<std::tuple<size_t, size_t>, T>& m_points;
	size_t m_rowIdx;
};

/// \brief Infinite matrix class
template<typename T>
class Matrix
{
public:
	/// \brief Constructs an infinite matrix
	/// \param defaultValue value to use for unassigned cells
	Matrix(T defaultValue) : m_defaultValue(defaultValue) {}
	size_t size() const { return m_points.size(); }

	/// \brief Get matrix row
	/// \param idx row index to get
	MatrixRow<T> operator[](size_t idx) 
	{
		MatrixRow<T> res{ m_points, m_defaultValue, idx };
		return res;
	}

protected:
	class Iterator;
public:
	Iterator begin() { return Iterator{m_points.begin()}; }
	Iterator end() { return Iterator{ m_points.end() }; }

protected:
	/// default value for unassigned cells
	T m_defaultValue;

	/// points assigned by user
	using key_type = std::tuple<size_t, size_t>;
	using points_type = std::map<key_type, T>;
	points_type m_points;
 	
 
	/// Iterator class
	class Iterator
	{
	public:
		using iterator_type = typename points_type::iterator;
		Iterator(iterator_type pointsIt) : m_it(pointsIt) {}
		Iterator& operator++() { m_it++; return *this; }
		bool operator != (const Iterator& other) { return m_it != other.m_it; }
		iterator_type& operator*() { return m_it; }

	protected:
		iterator_type m_it;
	};
};