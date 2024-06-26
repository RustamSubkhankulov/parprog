#ifndef COMP_MATH_HPP
#define COMP_MATH_HPP

#include <stdint.h>
#include <functional>

class Comp_scheme {

public:

  using rside_func_type = std::function<double(uint64_t, uint64_t)>;
  using bound_func_type = std::function<double(double)>;

private:

  double h_m;
  double tau_m;

  uint64_t x_points_m;
  uint64_t t_points_m;

  double a_m;
  rside_func_type f_m;

  double** u = nullptr;
  double* data = nullptr;

public:

  Comp_scheme(double h, double tau, 
              uint64_t x_points, uint64_t t_points, double a, 
              rside_func_type f = [](uint64_t m, uint64_t k){ (void)m; (void)k; return 0; })
  : h_m(h), 
    tau_m(tau), 
    x_points_m(x_points), 
    t_points_m(t_points), 
    a_m(a), 
    f_m(f)
    {}

  Comp_scheme(const Comp_scheme& that) = delete;
  Comp_scheme& operator=(const Comp_scheme& that) = delete;

  Comp_scheme(Comp_scheme&& that)
  : h_m(that.h_m), 
    tau_m(that.tau_m), 
    x_points_m(that.x_points_m), 
    t_points_m(that.t_points_m), 
    a_m(that.a_m), 
    f_m(that.f_m),
    u(std::exchange(that.u, nullptr)),
    data(std::exchange(that.data, nullptr))
    {}

  Comp_scheme& operator=(Comp_scheme&& that) {
    
    swap(that);
    return *this;
  }

  double h() const noexcept { return h_m; }
  double tau() const noexcept { return tau_m; }

  uint64_t x_points() const noexcept { return x_points_m; }
  uint64_t t_points() const noexcept { return t_points_m; }

  double a() const noexcept { return a_m; }
  rside_func_type f() const 
  noexcept(std::is_nothrow_copy_constructible<rside_func_type>::value) { 
    return f_m; 
  }

  void allocate() {

    u = new double*[x_points_m];
    data = new double[x_points_m * t_points_m];

    for (uint64_t x_idx = 0; x_idx < x_points_m; ++x_idx) {
      u[x_idx] = data + x_idx * t_points_m;
    }
  }

  void free() {

    delete[] data;
    delete[] u;
  }

  void set_boundary_time(uint64_t m, bound_func_type psi) {

    for (uint64_t t_idx = 0; t_idx < t_points_m; ++t_idx) {
      set(m, t_idx, psi(t_idx * tau_m));
    }
  }

  void set_boundary_coord(uint64_t m_begin, uint64_t m_end, bound_func_type fi) {

    for (uint64_t x_idx = m_begin; x_idx < m_end; ++x_idx) {
      set(x_idx, 0, fi(x_idx * h_m));
    }
  }

  void compute(uint64_t m, uint64_t k) {
    
    auto diff = u[m+1][k] - u[m-1][k];
    u[m][k+1] = tau_m * (f_m(m, k) - a_m * diff / (2 * h_m)) + diff / 2;
  }

  void compute_range(uint64_t m_begin, uint64_t m_end, uint64_t k) {

    for (uint64_t m = m_begin; m < m_end; ++m) {

    #ifdef DEBUG
      std::cout << "computing u[" << m << "][" << k+1 << "]\n";
      std::cout << "u[" << m+1 << "][" << k << "]=" << u[m+1][k] << " ";
      std::cout << "u[" << m-1 << "][" << k << "]=" << u[m-1][k] << " ";
    #endif

      auto diff = u[m+1][k] - u[m-1][k];
      u[m][k+1] = tau_m * (f_m(m, k) - a_m * diff / (2 * h_m)) + diff / 2;

    #ifdef DEBUG
      std::cout << "u[" << m << "][" << k+1 << "]=" << u[m][k+1] << "\n";
    #endif
    }
  }

  double get(uint64_t m, uint64_t k) const noexcept { return u[m][k]; }
  
  void set(uint64_t m, uint64_t k, double val) noexcept { 

  #ifdef DEBUG
    std::cout << "u[" << m << "][" << k << "]=" << val << "\n";
  #endif

    u[m][k] = val; 
  }

  void swap(Comp_scheme& that) {

    std::swap(h_m, that.h_m); 
    std::swap(tau_m, that.tau_m); 
    std::swap(x_points_m, that.x_points_m); 
    std::swap(t_points_m, that.t_points_m); 
    std::swap(a_m, that.a_m); 
    std::swap(f_m, that.f_m);

    std::swap(u, that.u);
    std::swap(data, that.data);
  }
};

#endif
