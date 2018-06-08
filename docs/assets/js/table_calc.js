

class FormulaTable {
    // constructor(table_element, column_meaning, update_order) {
    constructor(table_element, column_meaning, update_order = undefined) {
        this.table_element = table_element;
        this.column_meaning = column_meaning;
        this.update_order = update_order;
    }


    addEventListenerForAllInputs(event_type) {
        // TODO
        console.log('event_type:', event_type);
    }

    // general helpers

    findRowFromVariable(variable_name) {
        let result_element = undefined;
        let rows = this.table_element.querySelectorAll('tbody > tr');
        // console.log('rows', rows);
        let row_iterator = rows.values();
        // console.log('row_iterator', row_iterator);

        let row = null;
        let current_name = null;
        do {
            row = row_iterator.next();
            // console.log('row', row);
            if (row.value) {
                let name_element = this.getElementByFunction(row.value, 'name');
                // console.log('name_element: ', name_element);
                current_name = this.getNameFromElement(name_element);
            }
            // console.log('current_name', current_name);
        } while (current_name !== variable_name && row.done === false);
        result_element = row.value;
        return result_element;
    }

    getElementByFunction(row, name) {
        let el_index = this.column_meaning.indexOf(name);
        let element = row.children[value_index];
        return element;
    }

    getTextFromFirstTextNodeFromElement(element) {
        let value = undefined;
        // find first real text node...
        // currently we just use the firstChild.
        // but eventually we need an TreeWalker that finds the first SHOW_TEXT
        // node...
        // https://stackoverflow.com/questions/6520192/how-to-get-the-text-node-of-an-element/34700627#34700627
        value = element.firstChild.nodeValue;
        // console.log('value:', value);
        return value;
    }

    // get helper

    getTextValueFromElement(element, child_index = 0) {
        let value = undefined;
        if (element.childElementCount > 0) {
            // there are multiple options.
            // if child_index == -1 get first TextNode
            if (child_index === -1) {
                value = this.getTextFromFirstTextNodeFromElement(element);
            } else {
                // try to get child with
                let child = element.children[child_index];
                if (child) {
                    value = this.getTextFromFirstTextNodeFromElement(child);
                }
            }
        } else {
            // get first Text Node
            value = this.getTextFromFirstTextNodeFromElement(element);
        }
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

    getValueFromElement(element) {
        let value = undefined;
        // check if element is input
        if (element.nodeName === 'INPUT') {
            // get value
            value = element.value;
        } else {
            // get content
            value = this.getTextValueFromElement(element);
        }
        return value;
    }

    getNameFromElement(element) {
        let name_value = undefined;
        let name_raw = this.getTextFromFirstTextNodeFromElement(element);
        // console.log('name_raw:', name_raw);
        // trim raw value to contain only first allowed variable_name
        let name_regex = /(^[a-zA-z]+(?:[a-zA-z_0-9]+)?)\b/;
        let regex_result = name_regex.exec(name_raw);
        if (regex_result) {
            // get first capture group
            name_value = regex_result[1];
        }
        // console.log('name_value:    ', name_value);
        return name_value;
    }

    // get value / formula

    getFormulaFromVariable(variable_name) {
        let value = undefined;
        let row = this.findRowFromVariable(variable_name);
        let element = getElementByFunction(row, 'formula');
        value = this.getTextFromFirstTextNodeFromElement(element);
        return value;
    }

    getValueFromVariable(variable_name) {
        let value = undefined;
        let row = this.findRowFromVariable(variable_name);
        let value_element = getElementByFunction(row, 'value');
        value = this.getValueFromElement(value_element);
        return value;
    }

    getValue(variable_name) {
        let value = undefined;
        value = parseFloat(this.getValueFromVariable(variable_name));
        return value;
    }

    // set name / value / formula

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



    // update helper

    getFirstVariable() {
        let first_row = this.table_element.querySelector('tbody tr');
        let element = this.getElementByFunction(first_row, 'name');
        let variable_name = getNameFromElement(element);
        return variable_name;
    }

    // updates

    update_table(event) {
        console.log('update_table:', event);
        let first_Variable = this.getFirstVariable();
    }

    update_table_below(event) {
        console.log('update_table_below:', event);
    }

};
