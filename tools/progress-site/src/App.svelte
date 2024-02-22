<script>
    import Button from './components/Button.svelte';
    import ButtonContainer from './components/ButtonContainer.svelte';
    import ProgressPanel from './components/ProgressPanel.svelte';
    import { selectedOption } from './store.js';
</script>

<main>
    <h1>Melee Decompilation</h1>
    <div class="flex-container">
        <ButtonContainer>
            <Button optionId={0}>Introduction</Button>
            <Button optionId={1}>Progress</Button>
        </ButtonContainer>
        <div
            style="display: flex; flex-direction: column; justifiy-content: center; margin-top: 30px; width: 100%;"
        >
            {#if $selectedOption === 0}
                <div class="description">
                    GitHub: <a target="_blank" href="https://github.com/doldecomp/melee"
                        >https://github.com/doldecomp/melee</a
                    ><br />
                    Discord:
                    <a target="_blank" href="https://discord.gg/hKx3FJJgrV"
                        >https://discord.gg/hKx3FJJgrV</a
                    >
                </div>
            {:else if $selectedOption === 1}
                <ProgressPanel />
            {/if}
        </div>
    </div>
</main>

<style>
    main {
        text-align: center;
        padding: 10px;
        max-width: 240px;
        margin: 0 auto;
    }

    h1 {
        color: white;
        text-transform: uppercase;
        font-size: 48px;
    }

    .description {
        color: white;
        font-size: 24px;
        overflow: auto;
    }

    @media (min-width: 640px) {
        main {
            max-width: none;
        }
    }

    .flex-container {
        display: flex;
        flex-direction: row;
    }

    @media (max-width: 1300px) {
        main {
            padding: 5px;
            max-width: fit-content;
        }

        .flex-container {
            flex-direction: column;
            justify-content: center;
        }

        h1 {
            font-size: 24px;
        }
    }
</style>
