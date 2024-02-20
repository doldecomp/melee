<div class="buttonContainer"><slot /></div>

<style>
    .buttonContainer {
        margin-left: 100px;
        text-align: center;
    }

    @media (max-width: 1300px) {
        .buttonContainer {
            display: flex;
            justify-content: center;
            margin: 0;
        }
    }
</style>
