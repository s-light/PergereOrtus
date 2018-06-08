
// how to use the table_calc addon:
//
// - include the formula_parser.js file
// - add the following js after the table you want to use

// ---8<------------------------------------------
window.addEventListener('load', function(event) {
    console.log('All resources finished loading!');
    init();
});

var getValue = undefined;
var myFormulaTable = undefined;

function init() {
    console.group('init for table_calc...');

    let bt_update = document.querySelector('#bt_update');
    // find nearest table
    let table_element = findNearestInTree(bt_update, 'table');
    console.log('table_element', table_element);

    // x = findNearestInTree(document.querySelector('#bt_update'), 'table');
    // x.querySelectorAll('tbody > tr')


    let column_meaning = [
        'name',
        'test',
        'formula',
        'value',
    ];

    // let order = [
    //     'updates_per_second',                   // input
    //     'rpm',
    //     'pixel_pitch',                          // input
    //     'needle_diameter',                      // input
    //     'needle_active_radius',
    //     'pixel_count_one_side',
    //     'pixel_count_total',                    // input
    //     'pixel_circumference',
    //     'pixel_circumference_virtual_count',    // input
    //     'pixel_updates_per_revolution',
    //     'pixel_updates_per_second',
    //     'pixel_updates_per_minute',
    //     'duration_per_revolution',
    //     'duration_per_pixel',
    //     'pixel_pwm_rate_for_8bit',
    //     'pixel_pwm_rate_for_10bit',
    //     'pixel_pwm_rate_for_12bit',
    //     'pixel_pwm_rate_for_16bit',
    // ];

    // myFormulaTable = new FormulaTable(table_element, column_meaning, order);
    myFormulaTable = new FormulaTable(table_element, column_meaning);
    // map instance internal getValue to global getValue
    getValue = myFormulaTable.getValue;

    bt_update.addEventListener('click', myFormulaTable.update_table);

    myFormulaTable.addEventListenerForAllInputs('change');
    // let input_updates_per_second =
    //     document.querySelector('#updates_per_second');
    // input_updates_per_second.addEventListener(
    //     'change', myFormulaTable.update_table_below);

    console.groupEnd();
}
// ---8<------------------------------------------
