#include "cmod_csp_trough_eqns.h"
#include "cmod_csp_common_eqns.h"
#include "vartab.h"
#include <cmath>

#pragma warning(disable: 4297)  // ignore warning: 'function assumed not to throw an exception but does'


void Physical_Trough_System_Design_Equations(ssc_data_t data)
{
    auto vt = static_cast<var_table*>(data);
    if (!vt) {
        throw std::runtime_error("ssc_data_t data invalid");
    }

    double P_ref, gross_net_conversion_factor, csp_dtr_pwrb_nameplate,
        eta_ref, q_pb_design,
        radio_sm_or_area, specified_solar_multiple, total_aperture, total_required_aperture_for_SM1, solar_mult,
        q_rec_des,
        tshours, tshours_sf,
        specified_total_aperture, single_loop_aperture, nloops;
/*
    // csp_dtr_pwrb_nameplate
    ssc_data_t_get_number(data, "P_ref", &P_ref);
    ssc_data_t_get_number(data, "gross_net_conversion_factor", &gross_net_conversion_factor);
    csp_dtr_pwrb_nameplate = Nameplate(P_ref, gross_net_conversion_factor);
    ssc_data_t_set_number(data, "csp_dtr_pwrb_nameplate", csp_dtr_pwrb_nameplate);

    // q_pb_design
    //ssc_data_t_get_number(data, "P_ref", &P_ref);
    ssc_data_t_get_number(data, "eta_ref", &eta_ref);
    q_pb_design = Q_pb_design(P_ref, eta_ref);
    ssc_data_t_set_number(data, "q_pb_design", q_pb_design);

    // solar_mult
    ssc_data_t_get_number(data, "radio_sm_or_area", &radio_sm_or_area);
    ssc_data_t_get_number(data, "specified_solar_multiple", &specified_solar_multiple);
    ssc_data_t_get_number(data, "total_aperture", &total_aperture);
    ssc_data_t_get_number(data, "total_required_aperture_for_SM1", &total_required_aperture_for_SM1);
    solar_mult = Solar_mult(static_cast<int>(radio_sm_or_area), specified_solar_multiple, total_aperture, total_required_aperture_for_SM1);
    ssc_data_t_set_number(data, "solar_mult", solar_mult);

    // q_rec_des
    ssc_data_t_get_number(data, "solar_mult", &solar_mult);
    ssc_data_t_get_number(data, "q_pb_design", &q_pb_design);
    q_rec_des = Q_rec_des(solar_mult, q_pb_design);
    ssc_data_t_set_number(data, "q_rec_des", q_rec_des);

    // tshours_sf
    ssc_data_t_get_number(data, "tshours", &tshours);
    ssc_data_t_get_number(data, "solar_mult", &solar_mult);
    tshours_sf = Tshours_sf(tshours, solar_mult);
    ssc_data_t_set_number(data, "tshours_sf", tshours_sf);

    // nloops
    ssc_data_t_get_number(data, "radio_sm_or_area", &radio_sm_or_area);
    ssc_data_t_get_number(data, "specified_solar_multiple", &specified_solar_multiple);
    ssc_data_t_get_number(data, "total_required_aperture_for_SM1", &total_required_aperture_for_SM1);
    ssc_data_t_get_number(data, "specified_total_aperture", &specified_total_aperture);
    ssc_data_t_get_number(data, "single_loop_aperature", &single_loop_aperture);
    nloops = Nloops(static_cast<int>(radio_sm_or_area), specified_solar_multiple, total_required_aperture_for_SM1, specified_total_aperture, single_loop_aperture);
    ssc_data_t_set_number(data, "nloops", nloops);
*/
    double x = 1.;
}

void Physical_Trough_Solar_Field_Equations(ssc_data_t data)
{
    auto vt = static_cast<var_table*>(data);
    if (!vt) {
        throw std::runtime_error("ssc_data_t data invalid");
    }

    // Inputs
    double P_ref, gross_net_conversion_factor,
        eta_ref,
        T_loop_in_des, T_loop_out, Fluid,
        csp_dtr_sca_aperture_1, csp_dtr_sca_aperture_2, csp_dtr_sca_aperture_3, csp_dtr_sca_aperture_4,
        csp_dtr_hce_diam_absorber_inner_1, csp_dtr_hce_diam_absorber_inner_2, csp_dtr_hce_diam_absorber_inner_3, csp_dtr_hce_diam_absorber_inner_4,
        I_bn_des, csp_dtr_hce_design_heat_loss_1, csp_dtr_hce_design_heat_loss_2, csp_dtr_hce_design_heat_loss_3, csp_dtr_hce_design_heat_loss_4,
        csp_dtr_sca_length_1, csp_dtr_sca_length_2, csp_dtr_sca_length_3, csp_dtr_sca_length_4,
        csp_dtr_sca_calc_sca_eff_1, csp_dtr_sca_calc_sca_eff_2, csp_dtr_sca_calc_sca_eff_3, csp_dtr_sca_calc_sca_eff_4,
        csp_dtr_hce_optical_eff_1, csp_dtr_hce_optical_eff_2, csp_dtr_hce_optical_eff_3, csp_dtr_hce_optical_eff_4,
        m_dot_htfmax, fluid_dens_outlet_temp,
        m_dot_htfmin, fluid_dens_inlet_temp,
        radio_sm_or_area, specified_solar_multiple, specified_total_aperture,
        tshours,
        Row_Distance, csp_dtr_sca_w_profile_1, csp_dtr_sca_w_profile_2, csp_dtr_sca_w_profile_3, csp_dtr_sca_w_profile_4,
        non_solar_field_land_area_multiplier,
        nSCA, SCA_drives_elec;


    // Outputs
    double csp_dtr_pwrb_nameplate,
        q_pb_design,
        field_htf_cp_avg,
        single_loop_aperature,
        min_inner_diameter,
        cspdtr_loop_hce_heat_loss,
        loop_optical_efficiency,
        max_field_flow_velocity,
        min_field_flow_velocity,
        required_number_of_loops_for_SM1,
        total_loop_conversion_efficiency,
        total_required_aperture_for_SM1,
        nLoops,
        total_aperture,
        field_thermal_output,
        solar_mult,
        q_rec_des,
        tshours_sf,
        fixed_land_area,
        total_land_area,
        total_tracking_power;

    util::matrix_t<ssc_number_t> field_fl_props, trough_loop_control, SCAInfoArray, SCADefocusArray,
        K_cpnt, D_cpnt, L_cpnt, Type_cpnt;

    // csp_dtr_pwrb_nameplate
    ssc_data_t_get_number(data, "P_ref", &P_ref);
    ssc_data_t_get_number(data, "gross_net_conversion_factor", &gross_net_conversion_factor);
    csp_dtr_pwrb_nameplate = Nameplate(P_ref, gross_net_conversion_factor);
    ssc_data_t_set_number(data, "csp_dtr_pwrb_nameplate", csp_dtr_pwrb_nameplate);

    // q_pb_design
    ssc_data_t_get_number(data, "eta_ref", &eta_ref);
    q_pb_design = Q_pb_design(P_ref, eta_ref);
    ssc_data_t_set_number(data, "q_pb_design", q_pb_design);

    // field_htf_cp_avg
    ssc_data_t_get_number(data, "T_loop_in_des", &T_loop_in_des);
    ssc_data_t_get_number(data, "T_loop_out", &T_loop_out);
    ssc_data_t_get_number(data, "Fluid", &Fluid);
    ssc_data_t_get_matrix(vt, "field_fl_props", field_fl_props);
    field_htf_cp_avg = Field_htf_cp_avg(T_loop_in_des, T_loop_out, Fluid, field_fl_props);      // [kJ/kg-K]
    ssc_data_t_set_number(data, "field_htf_cp_avg", field_htf_cp_avg);

    // single_loop_aperature
    ssc_data_t_get_matrix(vt, "trough_loop_control", trough_loop_control);
    ssc_data_t_get_number(data, "csp_dtr_sca_aperture_1", &csp_dtr_sca_aperture_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_aperture_2", &csp_dtr_sca_aperture_2);
    ssc_data_t_get_number(data, "csp_dtr_sca_aperture_3", &csp_dtr_sca_aperture_3);
    ssc_data_t_get_number(data, "csp_dtr_sca_aperture_4", &csp_dtr_sca_aperture_4);
    single_loop_aperature = Single_loop_aperature(trough_loop_control, csp_dtr_sca_aperture_1,
        csp_dtr_sca_aperture_2, csp_dtr_sca_aperture_3, csp_dtr_sca_aperture_4);
    ssc_data_t_set_number(data, "single_loop_aperature", single_loop_aperature);

    // min_inner_diameter
    ssc_data_t_get_number(data, "csp_dtr_hce_diam_absorber_inner_1", &csp_dtr_hce_diam_absorber_inner_1);
    ssc_data_t_get_number(data, "csp_dtr_hce_diam_absorber_inner_2", &csp_dtr_hce_diam_absorber_inner_2);
    ssc_data_t_get_number(data, "csp_dtr_hce_diam_absorber_inner_3", &csp_dtr_hce_diam_absorber_inner_3);
    ssc_data_t_get_number(data, "csp_dtr_hce_diam_absorber_inner_4", &csp_dtr_hce_diam_absorber_inner_4);
    min_inner_diameter = Min_inner_diameter(trough_loop_control, csp_dtr_hce_diam_absorber_inner_1,
        csp_dtr_hce_diam_absorber_inner_2, csp_dtr_hce_diam_absorber_inner_3, csp_dtr_hce_diam_absorber_inner_4);
    ssc_data_t_set_number(data, "min_inner_diameter", min_inner_diameter);

    // cspdtr_loop_hce_heat_loss
    ssc_data_t_get_number(data, "I_bn_des", &I_bn_des);
    ssc_data_t_get_number(data, "csp_dtr_hce_design_heat_loss_1", &csp_dtr_hce_design_heat_loss_1);
    ssc_data_t_get_number(data, "csp_dtr_hce_design_heat_loss_2", &csp_dtr_hce_design_heat_loss_2);
    ssc_data_t_get_number(data, "csp_dtr_hce_design_heat_loss_3", &csp_dtr_hce_design_heat_loss_3);
    ssc_data_t_get_number(data, "csp_dtr_hce_design_heat_loss_4", &csp_dtr_hce_design_heat_loss_4);
    ssc_data_t_get_number(data, "csp_dtr_sca_length_1", &csp_dtr_sca_length_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_length_2", &csp_dtr_sca_length_2);
    ssc_data_t_get_number(data, "csp_dtr_sca_length_3", &csp_dtr_sca_length_3);
    ssc_data_t_get_number(data, "csp_dtr_sca_length_4", &csp_dtr_sca_length_4);
    cspdtr_loop_hce_heat_loss = Cspdtr_loop_hce_heat_loss(trough_loop_control, I_bn_des,
        csp_dtr_hce_design_heat_loss_1, csp_dtr_hce_design_heat_loss_2,
        csp_dtr_hce_design_heat_loss_3, csp_dtr_hce_design_heat_loss_4,
        csp_dtr_sca_length_1, csp_dtr_sca_length_2, csp_dtr_sca_length_3, csp_dtr_sca_length_4,
        csp_dtr_sca_aperture_1, csp_dtr_sca_aperture_2, csp_dtr_sca_aperture_3, csp_dtr_sca_aperture_4);
    ssc_data_t_set_number(data, "cspdtr_loop_hce_heat_loss", cspdtr_loop_hce_heat_loss);

    // loop_optical_efficiency
    ssc_data_t_get_number(data, "csp_dtr_sca_calc_sca_eff_1", &csp_dtr_sca_calc_sca_eff_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_calc_sca_eff_2", &csp_dtr_sca_calc_sca_eff_2);
    ssc_data_t_get_number(data, "csp_dtr_sca_calc_sca_eff_3", &csp_dtr_sca_calc_sca_eff_3);
    ssc_data_t_get_number(data, "csp_dtr_sca_calc_sca_eff_4", &csp_dtr_sca_calc_sca_eff_4);
    ssc_data_t_get_number(data, "csp_dtr_hce_optical_eff_1", &csp_dtr_hce_optical_eff_1);
    ssc_data_t_get_number(data, "csp_dtr_hce_optical_eff_2", &csp_dtr_hce_optical_eff_2);
    ssc_data_t_get_number(data, "csp_dtr_hce_optical_eff_3", &csp_dtr_hce_optical_eff_3);
    ssc_data_t_get_number(data, "csp_dtr_hce_optical_eff_4", &csp_dtr_hce_optical_eff_4);
    loop_optical_efficiency = Loop_optical_efficiency(trough_loop_control,
        csp_dtr_sca_calc_sca_eff_1, csp_dtr_sca_calc_sca_eff_2,
        csp_dtr_sca_calc_sca_eff_3, csp_dtr_sca_calc_sca_eff_4,
        csp_dtr_sca_length_1, csp_dtr_sca_length_2, csp_dtr_sca_length_3, csp_dtr_sca_length_4,
        csp_dtr_hce_optical_eff_1, csp_dtr_hce_optical_eff_2,
        csp_dtr_hce_optical_eff_3, csp_dtr_hce_optical_eff_4);
    ssc_data_t_set_number(data, "loop_optical_efficiency", loop_optical_efficiency);

    // sca_info_array
    SCAInfoArray = Sca_info_array(trough_loop_control);
    ssc_data_t_set_matrix(data, "scainfoarray", SCAInfoArray);
    
    // sca_defocus_array
    SCADefocusArray = Sca_defocus_array(trough_loop_control);
    ssc_data_t_set_array(data, "scadefocusarray", SCADefocusArray.data(), SCADefocusArray.ncells());

    //
    // End of no calculated dependencies
    //


    // max_field_flow_velocity
    ssc_data_t_get_number(data, "m_dot_htfmax", &m_dot_htfmax);
    ssc_data_t_get_number(data, "fluid_dens_outlet_temp", &fluid_dens_outlet_temp);
    max_field_flow_velocity = Max_field_flow_velocity(m_dot_htfmax, fluid_dens_outlet_temp, min_inner_diameter);
    ssc_data_t_set_number(data, "max_field_flow_velocity", max_field_flow_velocity);

    // min_field_flow_velocity
    ssc_data_t_get_number(data, "m_dot_htfmin", &m_dot_htfmin);
    ssc_data_t_get_number(data, "fluid_dens_inlet_temp", &fluid_dens_inlet_temp);
    min_field_flow_velocity = Min_field_flow_velocity(m_dot_htfmin, fluid_dens_inlet_temp, min_inner_diameter);
    ssc_data_t_set_number(data, "min_field_flow_velocity", min_field_flow_velocity);

    // total_loop_conversion_efficiency
    total_loop_conversion_efficiency = Total_loop_conversion_efficiency(loop_optical_efficiency, cspdtr_loop_hce_heat_loss);
    ssc_data_t_set_number(data, "total_loop_conversion_efficiency", total_loop_conversion_efficiency);

    // total_required_aperture_for_SM1
    total_required_aperture_for_SM1 = Total_required_aperture_for_sm1(q_pb_design, I_bn_des, total_loop_conversion_efficiency);
    ssc_data_t_set_number(data, "total_required_aperture_for_sm1", total_required_aperture_for_SM1);

    // required_number_of_loops_for_SM1
    required_number_of_loops_for_SM1 = Required_number_of_loops_for_SM1(total_required_aperture_for_SM1, single_loop_aperature);
    ssc_data_t_set_number(data, "required_number_of_loops_for_sm1", required_number_of_loops_for_SM1);

    // nloops
    ssc_data_t_get_number(data, "radio_sm_or_area", &radio_sm_or_area);
    ssc_data_t_get_number(data, "specified_solar_multiple", &specified_solar_multiple);
    ssc_data_t_get_number(data, "specified_total_aperture", &specified_total_aperture);
    nLoops = Nloops(static_cast<int>(radio_sm_or_area), specified_solar_multiple, total_required_aperture_for_SM1, specified_total_aperture, single_loop_aperature);
    ssc_data_t_set_number(data, "nloops", nLoops);

    // total_aperture
    total_aperture = Total_aperture(single_loop_aperature, nLoops);
    ssc_data_t_set_number(data, "total_aperture", total_aperture);

    // field_thermal_output
    field_thermal_output = Field_thermal_output(I_bn_des, total_loop_conversion_efficiency, total_aperture);
    ssc_data_t_set_number(data, "field_thermal_output", field_thermal_output);

    // solar_mult
    solar_mult = Solar_mult(static_cast<int>(radio_sm_or_area), specified_solar_multiple, total_aperture, total_required_aperture_for_SM1);
    ssc_data_t_set_number(data, "solar_mult", solar_mult);

    // Q_rec_des
    q_rec_des = Q_rec_des(solar_mult, q_pb_design);
    ssc_data_t_set_number(data, "q_rec_des", q_rec_des);

    // tshours_sf
    ssc_data_t_get_number(data, "tshours", &tshours);
    tshours_sf = Tshours_sf(tshours, solar_mult);
    ssc_data_t_set_number(data, "tshours_sf", tshours_sf);

    // fixed_land_area
    ssc_data_t_get_number(data, "Row_Distance", &Row_Distance);
    ssc_data_t_get_number(data, "csp_dtr_sca_w_profile_1", &csp_dtr_sca_w_profile_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_w_profile_2", &csp_dtr_sca_w_profile_2);
    ssc_data_t_get_number(data, "csp_dtr_sca_w_profile_3", &csp_dtr_sca_w_profile_3);
    ssc_data_t_get_number(data, "csp_dtr_sca_w_profile_4", &csp_dtr_sca_w_profile_4);
    fixed_land_area = Fixed_land_area(total_aperture, Row_Distance, SCAInfoArray,
        csp_dtr_sca_w_profile_1, csp_dtr_sca_w_profile_2, csp_dtr_sca_w_profile_3, csp_dtr_sca_w_profile_4);
    ssc_data_t_set_number(data, "fixed_land_area", fixed_land_area);

    // total_land_area
    ssc_data_t_get_number(data, "non_solar_field_land_area_multiplier", &non_solar_field_land_area_multiplier);
    total_land_area = Total_land_area(fixed_land_area, non_solar_field_land_area_multiplier);
    ssc_data_t_set_number(data, "total_land_area", total_land_area);

    // total_tracking_power
    ssc_data_t_get_number(data, "nSCA", &nSCA);
    ssc_data_t_get_number(data, "SCA_drives_elec", &SCA_drives_elec);
    total_tracking_power = Total_tracking_power(static_cast<int>(nSCA), static_cast<int>(nLoops), SCA_drives_elec);
    ssc_data_t_set_number(data, "total_tracking_power", total_tracking_power);

    // K_cpnt
    K_cpnt = K_Cpnt(static_cast<int>(nSCA));
    ssc_data_t_set_matrix(data, "k_cpnt", K_cpnt);

    // D_cpnt
    D_cpnt = D_Cpnt(static_cast<int>(nSCA));
    ssc_data_t_set_matrix(data, "d_cpnt", D_cpnt);

    // L_cpnt
    L_cpnt = L_Cpnt(static_cast<int>(nSCA));
    ssc_data_t_set_matrix(data, "l_cpnt", L_cpnt);

    // Type_cpnt
    Type_cpnt = Type_Cpnt(static_cast<int>(nSCA));
    ssc_data_t_set_matrix(data, "type_cpnt", Type_cpnt);

    /*
    double x = 1.;
    */
}

void Physical_Trough_Collector_Type_Equations(ssc_data_t data)
{
    auto vt = static_cast<var_table*>(data);
    if (!vt) {
        throw std::runtime_error("ssc_data_t data invalid");
    }

    // Inputs
    double csp_dtr_sca_length_1, csp_dtr_sca_ncol_per_sca_1,
        csp_dtr_sca_ave_focal_len_1, csp_dtr_sca_piping_dist_1,
        tilt, azimuth,
        nSCA,
        csp_dtr_sca_tracking_error_1, csp_dtr_sca_geometry_effects_1, csp_dtr_sca_clean_reflectivity_1, csp_dtr_sca_mirror_dirt_1, csp_dtr_sca_general_error_1,
        lat;

    // Outputs
    double csp_dtr_sca_ap_length_1,
        csp_dtr_sca_calc_theta_1,
        csp_dtr_sca_calc_end_gain_1,
        csp_dtr_sca_calc_zenith_1,
        csp_dtr_sca_calc_costh_1,
        csp_dtr_sca_calc_end_loss_1,
        csp_dtr_sca_calc_sca_eff_1,
        csp_dtr_sca_calc_latitude_1,
        csp_dtr_sca_calc_iam_1;

    util::matrix_t<ssc_number_t> IAMs_1;

    // csp_dtr_sca_ap_length
    ssc_data_t_get_number(data, "csp_dtr_sca_length_1", &csp_dtr_sca_length_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_ncol_per_sca_1", &csp_dtr_sca_ncol_per_sca_1);
    csp_dtr_sca_ap_length_1 = Csp_dtr_sca_ap_length(csp_dtr_sca_length_1, csp_dtr_sca_ncol_per_sca_1);
    ssc_data_t_set_number(data, "csp_dtr_sca_ap_length_1", csp_dtr_sca_ap_length_1);

    // csp_dtr_sca_calc_theta
    ssc_data_t_get_number(data, "lat", &lat);
    csp_dtr_sca_calc_theta_1 = Csp_dtr_sca_calc_theta(lat);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_theta_1", csp_dtr_sca_calc_theta_1);

    // csp_dtr_sca_calc_end_gain
    ssc_data_t_get_number(data, "csp_dtr_sca_ave_focal_len_1", &csp_dtr_sca_ave_focal_len_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_piping_dist_1", &csp_dtr_sca_piping_dist_1);
    csp_dtr_sca_calc_end_gain_1 = Csp_dtr_sca_calc_end_gain(csp_dtr_sca_ave_focal_len_1, csp_dtr_sca_calc_theta_1, csp_dtr_sca_piping_dist_1);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_end_gain_1", csp_dtr_sca_calc_end_gain_1);

    // csp_dtr_sca_calc_zenith
    csp_dtr_sca_calc_zenith_1 = Csp_dtr_sca_calc_zenith(lat);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_zenith_1", csp_dtr_sca_calc_zenith_1);

    // csp_dtr_sca_calc_costh
    ssc_data_t_get_number(data, "tilt", &tilt);
    ssc_data_t_get_number(data, "azimuth", &azimuth);
    csp_dtr_sca_calc_costh_1 = Csp_dtr_sca_calc_costh(csp_dtr_sca_calc_zenith_1, tilt, azimuth);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_costh_1", csp_dtr_sca_calc_costh_1);

    // csp_dtr_sca_calc_end_loss
    ssc_data_t_get_number(data, "nSCA", &nSCA);
    csp_dtr_sca_calc_end_loss_1 = Csp_dtr_sca_calc_end_loss(csp_dtr_sca_ave_focal_len_1, csp_dtr_sca_calc_theta_1, nSCA,
        csp_dtr_sca_calc_end_gain_1, csp_dtr_sca_length_1, csp_dtr_sca_ncol_per_sca_1);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_end_loss_1", csp_dtr_sca_calc_end_loss_1);

    // csp_dtr_sca_calc_sca_eff
    ssc_data_t_get_number(data, "csp_dtr_sca_tracking_error_1", &csp_dtr_sca_tracking_error_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_geometry_effects_1", &csp_dtr_sca_geometry_effects_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_clean_reflectivity_1", &csp_dtr_sca_clean_reflectivity_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_mirror_dirt_1", &csp_dtr_sca_mirror_dirt_1);
    ssc_data_t_get_number(data, "csp_dtr_sca_general_error_1", &csp_dtr_sca_general_error_1);
    csp_dtr_sca_calc_sca_eff_1 = Csp_dtr_sca_calc_sca_eff(csp_dtr_sca_tracking_error_1, csp_dtr_sca_geometry_effects_1,
        csp_dtr_sca_clean_reflectivity_1, csp_dtr_sca_mirror_dirt_1, csp_dtr_sca_general_error_1);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_sca_eff_1", csp_dtr_sca_calc_sca_eff_1);

    // csp_dtr_sca_calc_latitude
    csp_dtr_sca_calc_latitude_1 = Csp_dtr_sca_calc_latitude(lat);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_latitude_1", csp_dtr_sca_calc_latitude_1);

    // csp_dtr_sca_calc_iam
    ssc_data_t_get_matrix(vt, "IAMs_1", IAMs_1);
    csp_dtr_sca_calc_iam_1 = Csp_dtr_sca_calc_iam(IAMs_1, csp_dtr_sca_calc_theta_1, csp_dtr_sca_calc_costh_1);
    ssc_data_t_set_number(data, "csp_dtr_sca_calc_iam_1", csp_dtr_sca_calc_iam_1);
}
