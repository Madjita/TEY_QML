function dp(pixelDensity,x) {
    return (pixelDensity * 25.4 < 120) ? x : x*(pixelDensity * 25.4/160);
}

function baseColor() {
    return "#f26e35"
}

function primaryColor() {
    return "#d04828"
}

function textColor() {
    return "#434f4d"
}

function textAltColor() {
    return "#a6aaa2"
}

function backgroundColor() {
    return "#e7e8e9"
}

function backgroundAltColor() {
    return "#ffefde"
}

var CountLoadingFileBar = 0;

//var Rs = 0xe2;
//var Gs = 0xb6;
//var Bs = 0x2f;

var Rs = 0xff;
var Gs = 0x00;
var Bs = 0x00;

var Re = 0x9f;
var Ge = 0xcd;
var Be = 0x61;

var stepR = Re-Rs;
var stepG = Ge-Gs;
var stepB = Be-Bs;

var Rse =Rs;
var Gse =Gs;
var Bse = Bs;

function myColorAnimation(rows)
{

    stepR = (Re - Rs) / rows
    stepG = (Ge - Gs) / rows
    stepB = (Be - Bs) / rows

    Rse += stepR
    Gse += stepG
    Bse += stepB

}

