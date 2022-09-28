<script lang="ts" setup>
import { horse } from '../../../jslib/src/client'
let invoke = async () => {
  let result = await horse.invoke('testtest', { abc: 'allen1' })
  console.log(result)
}
</script>
<template>
  <div class="demoBtn" @click="invoke">Invoke</div>
</template>
