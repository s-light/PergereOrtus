
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
        'value',
        'formula',
    ];

    // let order = [
    //     'updates_per_second',                   // input
    //     'rpm',
    //     'pixel_pitch',                          // input
    // ........
    // ];

    // myFormulaTable = new FormulaTable(table_element, column_meaning, order);
    myFormulaTable = new FormulaTable(table_element, column_meaning);

    myFormulaTable.addEventListenerForAllInputs('change');
    bt_update.addEventListener('click', event => {
        myFormulaTable.update_table(event);
    });

    myFormulaTable.update_table();

    console.groupEnd();
}
// ---8<------------------------------------------
