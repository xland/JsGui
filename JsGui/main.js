//import * as os from 'os'
import * as std from "std";


//(function (g) {
//    let win = new Win();
//    os.setTimeout(() => {
//        win.close();
//    }, 3000);
//})(globalThis);


globalThis.win = new Win();
win.setRootFolder("ui");
win.show("index.html")
win.setSize(800, 600);