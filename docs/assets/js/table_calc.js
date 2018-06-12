

class FormulaTable {
    // constructor(table_element, column_meaning, update_order) {
    constructor(table_element, column_meaning, update_order = undefined) {
        this.table_element = table_element;
        this.column_meaning = column_meaning;
        this.update_order = update_order;

        // use global parser object
        this.parser = parser;
        this.parser.yy.getValue = vname => {return this.getValue(vname)};

        if (!this.update_order) {
            this.update_order = [];
            this.generateVariableUpdateOrder();
        }
    }


    // general helpers

    generateVariableUpdateOrder() {
        let rows = this.table_element.querySelectorAll('tbody > tr');
        for (let row of rows) {
            let name_element = this.getElementByFunction(row, 'name');
            // console.log('name_element: ', name_element);
            let current_name = this.getNameFromElement(name_element);
            this.update_order.push(current_name);
            // this.variable_row_map[current_name] = row;
        }
    }

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
        let element = row.children[el_index];
        return element;
    }

    getFirstTextNodeFromElement(element) {
        let firstTextNode = undefined;
        // find first real text node...
        // currently we just use the firstChild.
        // but eventually we need an TreeWalker that finds the first SHOW_TEXT
        // node...
        // https://stackoverflow.com/questions/6520192/how-to-get-the-text-node-of-an-element/34700627#34700627
        firstTextNode = element.firstChild;
        // console.log('element:', element);
        // console.log('firstTextNode:', firstTextNode);
        if (!firstTextNode) {
            // we have no text node found..
            // so we create an empty one..
            let new_node = document.createTextNode(' ');
            element.append(new_node);
            firstTextNode = element.firstChild;
        }
        return firstTextNode;
    }

    getTextFromFirstTextNodeFromElement(element) {
        let value = undefined;
        value = this.getFirstTextNodeFromElement(element).nodeValue;
        // console.log('value:', value);
        return value;
    }

    setTextFromFirstTextNodeFromElement(element, value) {
        this.getFirstTextNodeFromElement(element).nodeValue = value;
        // console.log('value:', value);
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
                    // console.log('child:', child);
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
        // console.log('element', element);
        // check if element is input
        if (element.firstElementChild.nodeName === 'LABEL') {
            element = element.firstElementChild;
        }
        if (element.firstElementChild.nodeName === 'INPUT') {
            // get value
            value = element.firstElementChild.value;
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

    // set helper

    setTextValueFromElement(element, value, child_index = 0) {

        if (element.childElementCount > 0) {
            // there are multiple options.
            // if child_index == -1 get first TextNode
            if (child_index === -1) {
                this.setTextFromFirstTextNodeFromElement(element, value);
            } else {
                // try to get child with
                let child = element.children[child_index];
                if (child) {
                    // console.log('child:', child);
                    this.setTextFromFirstTextNodeFromElement(child, value);
                }
            }
        } else {
            // get first Text Node
            this.setTextFromFirstTextNodeFromElement(element, value);
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
    }


    setValueFromElement(element, value) {
        // check if element is input
        if (element.firstElementChild.nodeName === 'LABEL') {
            element = element.firstElementChild;
        }
        if (element.firstElementChild.nodeName === 'INPUT') {
            // set value
            element.firstElementChild.value = value;
        } else {
            // set content
            this.setTextValueFromElement(element, value);
        }
    }

    // get value / formula

    getFormulaFromVariable(variable_name) {
        let value = undefined;
        let row = this.findRowFromVariable(variable_name);
        let element = this.getElementByFunction(row, 'formula');
        value = this.getTextFromFirstTextNodeFromElement(element);
        return value;
    }

    getValueFromVariable(variable_name) {
        let value = undefined;
        // console.log('variable_name', variable_name);
        let row = this.findRowFromVariable(variable_name);
        // console.log('row', row);
        if (row) {
            let value_element = this.getElementByFunction(row, 'value');
            value = this.getValueFromElement(value_element);
        } else {
            throw 'variable_name \'' + variable_name + '\' not found.';
        }
        return value;
    }

    getValue(variable_name) {
        let value = undefined;
        value = parseFloat(this.getValueFromVariable(variable_name));
        return value;
    }

    // set name / value / formula

    setValueFromVariable(variable_name, value) {
        let row = this.findRowFromVariable(variable_name);
        let value_element = this.getElementByFunction(row, 'value');
        this.setValueFromElement(value_element, value);
    }



    // update helper

    getFirstVariable() {
        let first_row = this.table_element.querySelector('tbody tr');
        let element = this.getElementByFunction(first_row, 'name');
        let variable_name = this.getNameFromElement(element);
        return variable_name;
    }

    // updates

    updateRowWithVariable(variable_name) {
        // console.log('updateRowWithVariable:', variable_name);
        let formula = this.getFormulaFromVariable(variable_name);
        // console.log('formula: \'' + formula + '\'');
        if (formula.length > 1) {
            // console.log('try to parse...');
            let result = this.parser.parse(formula);
            // console.log('result', result);
            this.setValueFromVariable(variable_name, result);
        }
    }

    update_table_below_Variable(variable_name) {
        // console.log('update_table_below_Variable:', variable_name);
        if (this.update_order.indexOf(variable_name) > -1) {
            for (
                var index = this.update_order.indexOf(variable_name) + 1;
                index < this.update_order.length;
                index++)
            {
                let variable_name = this.update_order[index];
                // console.log('variable_name:', variable_name, 'index', index);
                this.updateRowWithVariable(variable_name);
            }
        }
    }



    update_table(event) {
        // console.log('update_table:', event);
        let first_Variable = this.getFirstVariable();
        this.update_table_below_Variable(first_Variable);
    }

    update_table_below(event) {
        // console.log('update_table_below:', event);
        // extract variable_name from current event target
        // get row
        let row = event.target.closest('tr');
        let element = this.getElementByFunction(row, 'name');
        let variable_name = this.getNameFromElement(element);
        this.update_table_below_Variable(variable_name);
    }

    // others

    addEventListenerForAllInputs(event_type) {
        // console.log('event_type:', event_type);
        let all_inputs = this.table_element.querySelectorAll('input');
        for (let input_el of all_inputs) {
            // input_el.addEventListener(event_type, function(event) {
            //     console.log(this);
            //     this.update_table_below(event);
            // });
            input_el.addEventListener(
                event_type,
                event => {
                    // console.log(this);
                    this.update_table_below(event);
                }
            );
        }
    }
};
