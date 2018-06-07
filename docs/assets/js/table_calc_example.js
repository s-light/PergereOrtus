
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
    let table_element = null;
    // let table_element = findNearest(bt_update, 'table');
    // console.log('table_element', table_element);
    // console.group('findNearest(*bt_update*, \'table\')');
    // console.log('!! result:', findNearest(bt_update, 'table'));
    // console.groupEnd();
    // console.log('\n---------');

    // test for siblings
    // console.group('findNearest(*#world*, \'table\')');
    // console.log(
    //     '!! result:',
    //     findNearest(document.querySelector('#world'), 'table')
    // );
    // console.groupEnd();

    // test for children
    console.group('findNearest(*#test-children*, \'table\')');
    console.log(
        '!! result:',
        findNearest(document.querySelector('#test-children'), 'table')
    );
    console.groupEnd();

    // test for parent
    console.group('findNearest(*#test-parent*, \'table\')');
    console.log(
        '!! result:',
        findNearest(document.querySelector('#test-parent'), 'table')
    );
    console.groupEnd();


    // findNearest(document.querySelector('#leds'), 'table');



    let column_meaning = [
        'name',
        'test',
        'formula',
        'value',
    ];

    let order = [
        'updates_per_second',                   // input
        'rpm',
        'pixel_pitch',                          // input
        'needle_diameter',                      // input
        'needle_active_radius',
        'pixel_count_one_side',
        'pixel_count_total',                    // input
        'pixel_circumference',
        'pixel_circumference_virtual_count',    // input
        'pixel_updates_per_revolution',
        'pixel_updates_per_second',
        'pixel_updates_per_minute',
        'duration_per_revolution',
        'duration_per_pixel',
        'pixel_pwm_rate_for_8bit',
        'pixel_pwm_rate_for_10bit',
        'pixel_pwm_rate_for_12bit',
        'pixel_pwm_rate_for_16bit',
    ];

    myFormulaTable = new FormulaTable(table_element, column_meaning, order);
    // map instance internal getValue to global getValue
    getValue = myFormulaTable.getValue;

    bt_update.addEventListener('click', myFormulaTable.update_table);

    let input_updates_per_second =
        document.querySelector('#updates_per_second');
    input_updates_per_second.addEventListener(
        'change', myFormulaTable.update_table_below);

    console.groupEnd();
}
// ---8<------------------------------------------
