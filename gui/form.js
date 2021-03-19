
function init()
{

    Plotly.newPlot('ch',[createdata({ x : [1,2,1], y : [2,4,5]})],{});
}

function createdata(ctx)
{
    return {
        x : ctx.x,
        y : ctx.y,
        mode : 'markers'
    }
}

function build(ctx) {
    Plotly.newPlot('ch',[createdata(ctx)],{});
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
    if(res.code !== 0) return;
    build({ x : res.data[2], y : res.data[0] });
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