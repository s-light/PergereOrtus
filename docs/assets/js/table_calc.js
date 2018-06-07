

class FormulaTable {
    constructor(table_element, column_meaning, update_order) {
        this.table_element = table_element;
        this.column_meaning = column_meaning;
        this.update_order = update_order;
    }

    getValue(element_id) {
        let value = undefined;
        // let el = document.querySelector('#' + element_id);
        // if (el) {
        //     // check if element is input
        //     if (el.nodeName == 'INPUT') {
        //         // get value
        //         value = parseFloat(el.value);
        //     } else {
        //         // get content
        //         value = parseFloat(el.textContent);
        //     }
        // }
        return value;
    }

    setValue(element_id, value) {
        // let el = document.querySelector('#' + element_id);
        // if (el) {
        //     // check if element is input
        //     if (el.nodeName == 'INPUT') {
        //         // set value
        //         el.value = value;
        //     } else {
        //         // set content
        //         el.textContent = value;
        //     }
        // }
    }

    update_table(event) {
        console.log('update_table:', event);
    }

    update_table_below(event) {
        console.log('update_table_below:', event);
    }

};
