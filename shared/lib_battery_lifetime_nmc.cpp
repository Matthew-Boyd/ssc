#include "lib_battery_lifetime_calendar_cycle.h"
#include "lib_battery_lifetime_nmc.h"

void lifetime_nmc_t::initialize() {
    // cycle model for counting cycles only, no cycle-only degradation
    cycle_model = std::unique_ptr<lifetime_cycle_t>(new lifetime_cycle_t(params, state));
    // do any state initialization here
}

lifetime_nmc_t::lifetime_nmc_t(double dt_hr) {
    params = std::make_shared<lifetime_params>();
    params->model_choice = lifetime_params::NMCNREL;
    params->dt_hr = dt_hr;
    state = std::make_shared<lifetime_state>();
    initialize();
}

lifetime_nmc_t::lifetime_nmc_t(std::shared_ptr<lifetime_params> params_pt) {
    params = std::move(params_pt);
    initialize();
}

lifetime_nmc_t::lifetime_nmc_t(const lifetime_nmc_t &rhs) :
        lifetime_t(rhs){
    operator=(rhs);
}

lifetime_nmc_t& lifetime_nmc_t::operator=(const lifetime_nmc_t& rhs) {
    if (this != &rhs) {
        *params = *rhs.params;
        *state = *rhs.state;
    }
    return *this;
}

lifetime_t * lifetime_nmc_t::clone() {
    return new lifetime_nmc_t(*this);
}

void lifetime_nmc_t::runLifetimeModels(size_t lifetimeIndex, bool charge_changed, double prev_DOD, double DOD,
                                       double T_battery) {
    if (charge_changed)
        cycle_model->rainflow(prev_DOD);

    state->day_age_of_battery = (int)(lifetimeIndex / (util::hours_per_day / params->dt_hr));

}

double lifetime_nmc_t::estimateCycleDamage() {

}

void lifetime_nmc_t::replaceBattery(double percent_to_replace) {

}
