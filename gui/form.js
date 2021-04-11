
console.log('version 2.0');

function init()
{

    Plotly.newPlot('ch',createdata([{ x : [1,2,1], y : [2,4,5]}]),{});
}

function createdata(ctx)
{

    let data = [];
    for(let c of ctx)
    {
        data.push({
            x : c.x,
            y : c.y,
            name : c.name,
            mode : 'markers'
        })
    };

    return data;
}

function build(ctx) {
    Plotly.newPlot('ch',createdata(ctx),{});
}

init();

function readparams() {
    let root = document.getElementById('params');
    let elems = root.children;
    let data = {};
    for(let e of elems)
    {
        if(e.nodeName === 'INPUT') 
        {
            data[e.id] = e.value;
        }
    }
    return data;
    
}

function loaddata(res) {
    if(res.code !== 0) return console.log('NOT ZERO RETURN CODE');
    res.data = res.data.filter(x => x);
    let ctx = res.data.map(a => { return { x : a.content[2], y : a.content[1], name : a.name }; });
    build(ctx);
}

document.getElementById('calc').onclick = () => {
    let data = JSON.stringify(readparams());
    console.log(data);
    $.ajax('/calc', {
        type: 'POST',
        data : data,
        dataType : 'json',
        success : loaddata, 
        error : (err) => { console.error(err); },
        contentType : 'application/json'
    });
}
