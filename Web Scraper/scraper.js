async function downloadPage(url) {
    return await fetch(url).then(async response => {
        const text = await response.text();
        const page = document.createElement("div");
        page.innerHTML = text;
        return page;
    });
}
