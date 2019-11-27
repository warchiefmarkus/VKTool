function sendXHR(method, url, callback, data, contentType) {
    if (!method || !url) {
        return null
    }
    var request = new XMLHttpRequest()
    var requestUrl = (method === 'GET' ? '%1%2'.arg(url).arg(data ? "?%1".arg(data) : "") : url)

    request.open(method, requestUrl)

    request.onprogress = function(event) {
        console.log( 'Получено с сервера ' , event.loaded , ' байт из ' , event.total );
    }

    request.onreadystatechange = function() {
        if (request.readyState === XMLHttpRequest.DONE) {
            if (callback) {
                callback(request)
            }
        }
    }

    if (method !== 'GET') {
        request.setRequestHeader('Content-Type', contentType ? contentType
                                                             : 'application/x-www-form-urlencoded')
        request.setRequestHeader('Content-Length', data ? data.length : 0)
        request.send(data)     } else {         request.send()     }
    return request
}

function sendXHRLike(pid, method, url, callback, data, contentType) {
    if (!method || !url) {
        return null
    }
    var request = new XMLHttpRequest()
    var requestUrl = (method === 'GET' ? '%1%2'.arg(url).arg(data ? "?%1".arg(data) : "") : url)

    request.open(method, requestUrl)

    request.onprogress = function(event) {
        console.log( 'Получено с сервера ' , event.loaded , ' байт из ' , event.total );
    }

    request.onreadystatechange = function() {
        if (request.readyState === XMLHttpRequest.DONE) {
            if (callback) {
                callback(request, pid)
            }
        }
    }

    if (method !== 'GET') {
        request.setRequestHeader('Content-Type', contentType ? contentType
                                                             : 'application/x-www-form-urlencoded')
        request.setRequestHeader('Content-Length', data ? data.length : 0)
        request.send(data)     } else {         request.send()     }
    return request
}
