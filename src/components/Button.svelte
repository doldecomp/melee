<script>
    import { selectedOption } from '../store'

    export let optionId;
</script>

<div class={"button" + ($selectedOption === optionId ? " selected" : "")} on:mouseover={() => selectedOption.set(optionId)}><slot /></div>

<!-- <svg width="450" viewBox="55.089 96.472 253.537 65.653" xmlns="http://www.w3.org/2000/svg">
  <path style="fill: none; stroke: yellow; stroke-width: 3px;" d="M 55.089 139.216 L 77.339 96.472 L 308.626 97.643 L 308.04 159.125 L 71.484 157.368 L 55.089 139.216 Z"/>
</svg> -->

<style>
    /*
    .edge1 {
        position: absolute;
        transform-origin: 0 0;
        transform: translateX(-30px) translateY(62px) rotateZ(-67deg);
        height: 4px;
        width: 72px;
        background-color: yellow;
    }
    .edge2 {
        position: absolute;
        transform-origin: 0 0;
        transform: translateX(-26px) translateY(59.5px) rotateZ(37deg);
        height: 4px;
        width: 36px;
        background-color: yellow;
    }
    */
    .button {
        width: 450px;
        height: 80px;
        margin: 30px;
        
        background: transparent;
        border: 4px solid yellow;
        border-radius: 15px;
        color: yellow;
        font-weight: 800;
        font-size: 40px;
        line-height: 80px;
        text-align: center;
    }

    .button.selected {
        background-color: yellow;
        color: black;
    }

    @media (max-width: 1300px) {
		.button {
			margin-left: 10px;
            margin-right: 10px;
            font-size: 20px;
            width: 225px;
            height: 40px;
            line-height: 40px;
		}
	}
</style>